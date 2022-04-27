
/************************************************
 *
 * Geneardor de un caso de prueba.
 *
 *
 ***********************************************/


#include "stdio.h"
#include "stdint.h"

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
        {"05/02/2022 23:16:03", "AXJ 4843", 'G', 80, 1581},
        {"05/02/2022 23:16:02", "ABJ 3832", 'G', 45, 7851},
        {"05/02/2022 23:16:07", "CDJ 8617", 'G', 32, 4681},
        {"05/02/2022 23:16:00", "ACD 7080", 'G', 10, 7890},
        {"05/02/2022 23:16:05", "RTG 8595", 'G', 102, 6789},
        {"05/02/2022 23:16:04", "LKI 2304", 'G', 84, 3324},
        {"05/02/2022 23:16:06", "OPS 1411", 'G', 47, 1478},
        {"05/02/2022 23:16:09", "HHU 2249", 'G', 396, 1563},
        {"05/02/2022 23:16:01", "KUO 2971", 'G', 102, 4862},
        {"05/02/2022 23:16:08", "YHW 9588", 'G', 480, 1282},
};

char logBuffer[NUM_OF_TRANSACTIONS_TEST * LOG_LINE_SIZE];

int main()
{
    uint8_t *n = (uint8_t *)&t;
    FILE *f = fopen("DataTest.h","w");
    fprintf(f,"#define SIZE_OF_TRANSACTION 34\n");
    fprintf(f,"#define NUM_OF_TEST_TRANSACTIONS %i\n",NUM_OF_TRANSACTIONS_TEST);
    fprintf(f,"/* Datos simulados\n");
    fprintf(f,"05/02/2022 23:16:03, AXJ 4843, G , 80, 1581\n");
    fprintf(f,"05/02/2022 23:16:02, ABJ 3832, G , 45, 7851\n");
    fprintf(f,"05/02/2022 23:16:07, CDJ 8617, G , 32, 4681\n");
    fprintf(f,"05/02/2022 23:16:00, ACD 7080, G , 10, 7890\n");
    fprintf(f,"05/02/2022 23:16:05, RTG 8595, G , 102, 6789\n");
    fprintf(f,"05/02/2022 23:16:04, LKI 2304, G , 84, 3324\n");
    fprintf(f,"05/02/2022 23:16:06, OPS 1411, G , 47, 1478\n");
    fprintf(f,"05/02/2022 23:16:09, HHU 2249, G , 396, 1563\n");
    fprintf(f,"05/02/2022 23:16:01, KUO 2971, G , 102, 4862\n");
    fprintf(f,"05/02/2022 23:16:08, YHW 9588, G , 480, 1282\n");

    fprintf(f,"*/\n");
    fprintf(f,"const char data[SIZE_OF_TRANSACTION*NUM_OF_TEST_TRANSACTIONS] = {\n");
    for (size_t i = 0; i < NUM_OF_TRANSACTIONS_TEST; i++)
    {
        /* code */
        for (size_t j = 0; j < sizeof(PackedTransaction); j++)
        {
            //printf("%02X ", *n);
            fprintf(f,"0x%02X,", *n);
            n++;
        }
        fprintf(f,"\n");
    }
    fprintf(f,"};\n");
    fclose(f);


    return 0;
}
