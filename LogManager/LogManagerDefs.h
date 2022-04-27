#ifndef LOG_MANAGER_DEFS_H
#define LOG_MANAGER_DEFS_H

#include "LogManager.h"

/********** Definiciones **********/
#define MAX_TRANSACTION_COUNT 100
#define SIZE_OF_TRANSACTION_DATA 34
#define LOG_LINE_WIDTH 70

/**
 * Estructura para almacenar localmente los campos de
 * cada transacción
 * 
 */
typedef struct
{
    uint8_t timestamp[19];
    uint8_t vehicle_registration [8];
    uint8_t product;
    uint8_t mililiters[4];
    uint8_t transaction_id[2];
} TransactionData;

/**
 * Contexto local del log Manager
 * 
 */
typedef struct
{
    TransactionData transactionBuffer[MAX_TRANSACTION_COUNT];
    TransactionData *sortedTransactions[MAX_TRANSACTION_COUNT];
    uint8_t numOfTransactions;
} Context;

typedef struct
{
    char line [LOG_LINE_WIDTH];
} LogLine;
/********** Funciones Estáticas **********/

static void printLog(char *log);
static void printSingleLogLine(LogLine * line, uint8_t i);
static time_t getUnixtime(uint8_t i);

static void swapSortedTransactions(uint8_t i, uint8_t j);
static void copyTransactionsToBuffer(const char *data, size_t transaction_count);
static void sortTransactions(void);

#endif