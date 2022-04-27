#include "LogManagerDefs.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "time.h"

/************************* Variables locales *************************/

Context context;

/************************* Funciones Globales *************************/

int log_transactions(const char *data, char *log, size_t transaction_count)
{
    copyTransactionsToBuffer(data, transaction_count);
    sortTransactions();
    writeLog(log);
    return context.numOfTransactions;
}

/************************* Funciones Estáticas *************************/

void copyTransactionsToBuffer(const char *data, size_t transaction_count)
{
    TransactionData *transPtr = (TransactionData *)data;

    if (transaction_count > MAX_TRANSACTION_COUNT)
    {
        transaction_count = MAX_TRANSACTION_COUNT;
    }
    context.numOfTransactions = transaction_count;

    for (size_t i = 0; i < transaction_count; i++)
    {
        context.transactionBuffer[i] = *transPtr;
        context.sortedTransactions[i] = &context.transactionBuffer[i];

        transPtr++;
    }
}

static void sortTransactions(void)
{
    time_t min = 0;
    time_t aux = 0;
    size_t jmin = 0;
    for (size_t i = 0; i < context.numOfTransactions; i++)
    {
        min = getUnixtime(i);
        jmin = i;
        for (size_t j = i + 1; j < context.numOfTransactions; j++)
        {
            aux = getUnixtime(j);

            if (aux < min)
            {
                min = aux;
                jmin = j;
            }
        }
        swapSortedTransactions(i, jmin);
    }
}

static void swapSortedTransactions(uint8_t i, uint8_t j)
{
    TransactionData *aux;
    aux = context.sortedTransactions[i];
    context.sortedTransactions[i] = context.sortedTransactions[j];
    context.sortedTransactions[j] = aux;
}

static time_t getUnixtime(uint8_t i)
{
    int y, m, d, hour, min, sec;
    struct tm timeinfo;
    time_t unixTime;

    char timestamp[20];

    memcpy(timestamp, context.sortedTransactions[i]->timestamp, 19);
    timestamp[19] = 0;
    sscanf(timestamp, "%02d/%02d/%04d %02d:%02d:%02dlll", &d, &m, &y, &hour, &min, &sec);

    timeinfo.tm_year = y - 1900;
    timeinfo.tm_mon = m - 1;
    timeinfo.tm_mday = d;
    timeinfo.tm_hour = hour;
    timeinfo.tm_min = min;
    timeinfo.tm_sec = sec;

    unixTime = mktime(&timeinfo);

    return unixTime;
}
static void writeLog(char *log)
{
    LogLine *line = (LogLine *)log;
    for (size_t i = 0; i < context.numOfTransactions; i++)
    {
        writeSingleLogLine(line, i);
        line++;
    }
}

static void writeSingleLogLine(LogLine *line, uint8_t i)
{
    char timestamp[20];
    char reg[9];
    char prod;
    int32_t ltrs;
    uint16_t id;
    int y, m, d, hour, min, sec;

    memcpy(timestamp, context.sortedTransactions[i]->timestamp, 19);
    timestamp[19] = 0;
    sscanf(timestamp, "%02d/%02d/%04d %02d:%02d:%02d", &d, &m, &y, &hour, &min, &sec);
    memcpy(reg, context.sortedTransactions[i]->vehicle_registration, 8);
    reg[8] = 0;

    ltrs = *(int32_t *)&context.sortedTransactions[i]->mililiters;
    id = *(uint16_t *)&context.sortedTransactions[i]->transaction_id;
    prod = (char)context.sortedTransactions[i]->product;

    sprintf((char *)line, "[%02d/%02d/%02d %02d:%02d:%02d] id: %05i, reg: %s, prod: %c, ltrs: %+08i\n",
            d, m, y % 100, hour, min, sec,
            id,
            reg,
            prod,
            ltrs);
}