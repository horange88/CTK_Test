#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include "stdlib.h"
#include "stdint.h"

/**
 * @brief Escribe en log el registro de las transaction_count
 * transacciones contenidas en data
 * 
 * @param data puntero al buffer de transacciones
 * @param log puntero al buffer donde se escribirá el log
 * @param transaction_count cantidad de transacciones contenidas en data
 * @return int cantidad de transacciones procesadas
 */
int log_transactions(const char *data, char * log, size_t transaction_count);

#endif