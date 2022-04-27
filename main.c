
/************************************************
 * 
 * Caso de uso de la función que registra el log
 * de transacciones.
 * 
 * 
 ***********************************************/


#include "LogManager.h"
#include "time.h"
#include "stdio.h"

#define NUM_OF_TRANSACTIONS_TEST 10
#define LOG_LINE_SIZE 70

/**
 * @brief Estructura utilizada para simular el stream
 * de datos, sin padding.
 * 
 */
typedef struct
{
    char timestamp[19];
    char vehicle_registration[8];
    char product;
    int32_t mililiters;
    uint16_t transaction_id;
} __attribute__((packed)) PackedTransaction;

/**
 * Datos recibidos
 * 
 */
PackedTransaction t[NUM_OF_TRANSACTIONS_TEST] =
    {
        {"05/02/2022 23:16:03", "AXJ 3653", 'G', 80, 1581},
        {"05/02/2022 23:16:02", "AXJ 3652", 'G', 80, 1581},
        {"05/02/2022 23:16:07", "AXJ 3657", 'G', 80, 1581},
        {"05/02/2022 23:16:00", "AXJ 3650", 'G', 80, 1581},
        {"05/02/2022 23:16:05", "AXJ 3655", 'G', 80, 1581},
        {"05/02/2022 23:16:04", "AXJ 3654", 'G', 80, 1581},
        {"05/02/2022 23:16:06", "AXJ 3651", 'G', 80, 1581},
        {"05/02/2022 23:16:09", "AXJ 3659", 'G', 80, 1581},
        {"05/02/2022 23:16:01", "AXJ 3651", 'G', 80, 1581},
        {"05/02/2022 23:16:08", "AXJ 3658", 'G', 80, 1581},
};

char logBuffer[NUM_OF_TRANSACTIONS_TEST * LOG_LINE_SIZE];

int main()
{
    log_transactions((const char *)&t, (char *)logBuffer, 10);
    printf("%s", logBuffer);

    return 0;
}
