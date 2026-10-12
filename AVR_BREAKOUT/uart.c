/*
 * uart.c
 *
 *  Created on: 11 paź 2026
 *      Author: cichy
 */


#include <avr/io.h>
#include "uart.h"

void uart_init(uint32_t baudrate){
	uint16_t ubrr_val = (11059200/(16 * baudrate)) - 1;

	UBRRH = (unsigned char)(ubrr_val >> 8);
	UBRRL = (unsigned char)ubrr_val;

	UCSRB |= (1 << RXEN) | (1 << TXEN);

	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

void uart_transmit(char data){

	while(!(UCSRA & (1 << UDRE))){

	}
	UDR = data;
}

void uart_print(const char* str){
	while(*str){
		uart_transmit(*str++);
	}
}

char uart_reciver(void){
	if (UCSRA & (1 << RXC)){
		return UDR;
	}
	return 0;
}

