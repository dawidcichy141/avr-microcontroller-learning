/*
 * uart.h
 *
 *  Created on: 11 paź 2026
 *      Author: cichy
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void uart_init(uint32_t baudrate);

void uart_transmit(char data);

void uart_print(const char* str);

char uart_reciver(void);


#endif /* UART_H_ */
