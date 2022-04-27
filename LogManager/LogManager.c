#include "LogManagerDefs.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "time.h"

/********** Variables locales **********/

Context context;
/*
timestamp 19 ASCII en formato [mm/dd/yyyy hh:mm:ss]
vehicle_registration 8 ASCII en formato [AAA 1111]
product 1 Caracter ASCII imprimible
mililiters 4 Binario int32_t de mililitros despachados
transaction_id 2 Binario uint16_t

*/

/********** Funciones Globales **********/

int log_transactions(const char *data, char *log, size_t transaction_count)
{
    copyTransactionsToBuffer(data, transaction_count);
    sortTransactions();
    printLog(log);
    return context.numOfTransactions;
}

/********** Funciones Estáticas **********/
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
            //printSingleLogLine(i);
            aux = getUnixtime(j);

            if (aux < min)
            {
                min = aux;
                jmin = j;
            }
        }
        //last = min;
        swapSortedTransactions(i, jmin);
        //printf("jmin %i %i\n",i,jmin);
        //printSingleLogLine(i);
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

    char timestamp[20];

    memcpy(timestamp, context.sortedTransactions[i]->timestamp, 19);
    timestamp[19] = 0;
    //printf("%slll\n", timestamp);
    sscanf(timestamp, "%02d/%02d/%04d %02d:%02d:%02dlll", &d, &m, &y, &hour, &min, &sec);
    //printf(" parseado  %02i/%02i/%04i %02i:%02i:%02i\n", d, m, y, hour, min, sec);

    timeinfo.tm_year = y - 1900;
    timeinfo.tm_mon = m - 1;
    timeinfo.tm_mday = d;
    timeinfo.tm_hour = hour;
    timeinfo.tm_min = min;
    timeinfo.tm_sec = sec;

    time_t unixtime = mktime(&timeinfo);

    //printf(" unix  %lu\n", unixtime);
    return unixtime;

    //printf("sizeof(PackedTransaction) %li\n",sizeof(PackedTransaction));
    //printf("sizeof(Transaction) %li\n",sizeof(Transaction));
}
static void printLog(char *log)
{
    LogLine *line = (LogLine *)log;
    for (size_t i = 0; i < context.numOfTransactions; i++)
    {
        printSingleLogLine((LogLine *)line, i);
        line++;
    }
}

static void printSingleLogLine(LogLine *line, uint8_t i)
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

    //[05/02/22 23:16:27] id: 01581, reg: AXJ 3658, prod: G, ltrs: +0000080\n
    sprintf((char*)line, "[%02d/%02d/%02d %02d:%02d:%02d] id: %05i, reg: %s, prod: %c, ltrs: %+08i\n",
            d, m, y % 100, hour, min, sec,
            id,
            reg,
            prod,
            ltrs);
}