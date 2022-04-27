#ifndef LOG_MANAGER_DEFS_H
#define LOG_MANAGER_DEFS_H

#include "LogManager.h"

/************************* Definiciones *************************/
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
    uint8_t vehicle_registration[8];
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
    char line[LOG_LINE_WIDTH];
} LogLine;

/************************* Funciones Estáticas *************************/

/**
 * @brief Escribe en log los registros de transacciones
 * almacenados en el buffer local
 *
 * @param log puntero donde se escribira el log
 */
static void writeLog(char *log);

/**
 * @brief Escribe en line la el registro i almacenado
 * en el buffer local
 *
 * @param line puntero donde se copiara el registro
 * @param i registro que se desea copiar
 */
static void writeSingleLogLine(LogLine *line, uint8_t i);

/**
 * @brief Calcula el tiempo unix del registro i
 *
 * @param i indice del registro almacenado en el buffer local
 * @return time_t tiempo unix
 */
static time_t getUnixtime(uint8_t i);

/**
 * @brief Intercambia dos registros de transacciones i, j
 * almacenados en el buffer local entre sí
 *
 * @param i transacción a intercambiar
 * @param j transacción a intercambiar
 */
static void swapSortedTransactions(uint8_t i, uint8_t j);

/**
 * @brief Copia en el buffer local las transaction_count transacciones
 * apuntadas por data, hasta un máximo de 100 transaccinoes
 *
 * @param data puntero donde se encuentran las transacciones a copiar
 * @param transaction_count numero de transacciones a copiar
 */
static void copyTransactionsToBuffer(const char *data, size_t transaction_count);

/**
 * @brief Ordena las transacciones almacenadas en el buffer local
 *
 */
static void sortTransactions(void);

#endif