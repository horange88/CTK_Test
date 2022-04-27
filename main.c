
/************************************************
 *
 * Caso de uso de la función que registra el log
 * de transacciones.
 *
 *
 ***********************************************/

#include "LogManager.h"
#include "DataTest.h"
#include "time.h"
#include "stdio.h"

#define LOG_LINE_SIZE 70

char logBuffer[NUM_OF_TEST_TRANSACTIONS * LOG_LINE_SIZE];

int main()
{

    log_transactions(data, logBuffer, NUM_OF_TEST_TRANSACTIONS);
    printf("%s", logBuffer);

    return 0;
}
