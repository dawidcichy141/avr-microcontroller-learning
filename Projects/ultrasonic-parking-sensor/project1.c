/*
 * project1.c
 *
 *  Created on: 27 sie 2026
 *      Author: cichy
 */
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#define BAUDRATE 9600
#define MYUBRR ((F_CPU / (16UL * BAUDRATE)) - 1)
// Prowizoryczny czujnik parkowania z uzyciem czujnika ultradzwiekowego (US-105)



void uart_init(unsigned int ubrr){
	UBRRH = (unsigned char)(ubrr >> 8);
	UBRRL = (unsigned char)ubrr;

	UCSRB |= (1 << TXEN);
	UCSRB |= (1 << RXEN);

	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);


}

void uart_putc(unsigned char data){
	while(!(UCSRA & (1 << UDRE))){

	}
	UDR = data;
}

void uart_puts(const char *s){
	while(*s){
		uart_putc(*s++);

	}

}

char uart_getc(void) {
    if (UCSRA & (1 << RXC)){
    	return UDR;
    }
    else{
    	return 0;
    }
}

void print_menu(void) {
    uart_puts("\r\n--- MENU  ---\r\n");
    uart_puts(" O - Wyswietl pomiar odleglosci\r\n");
    uart_puts(" m - Wyswietl menu\r\n");
    uart_puts("---------------------\r\n");
}

int main(void){
	uart_init(MYUBRR);

	DDRC |= (1 << PC0);
	PORTC |= (1 << PC0);
	DDRC |= (1 << PC7);
	PORTC &= ~(1 << PC7);


	DDRC |= (1<< PC1);   //
	DDRC &= ~(1 << PC2); //



	print_menu();
	while(1){
		PORTC |= (1 << PC1);
		_delay_us(10);
		PORTC &= ~(1 << PC1);

		uint16_t timeout = 0;

		while(!(PINC & (1<< PC2))){
			timeout++;
			if(timeout > 60000) break;

		}
		if(timeout > 60000) continue;

		TCNT1 = 0;
		TCCR1B |= (1 << CS11);

		timeout = 0;

		while(PINC & (1<< PC2)){
			timeout++;
			if(timeout > 60000) break;

		}

		TCCR1B = 0;
		// v = 343 m/s = 34300cm/1000000us = 0,0343 cm/us  t = 1cm/0,0343cm/us = 29,15us
		int distance = TCNT1/58; //58 =  29,15us*2


		PORTC ^= (1 << PC0);
		PORTC ^= (1 << PC7);
		for (int i = 0; i < distance; i++){
			_delay_ms(1);
		}

		_delay_ms(50);



		char buffer[32];
		char c = uart_getc();
		if (c != 0){
			if(c == 'o' || c == 'O'){
				sprintf(buffer,"Odleglosc to: %d cm\r\n", distance);
				uart_puts(buffer);
				}
			else if (c == 'm' || c == 'M'){
				print_menu();
			}
			else{
				uart_puts("Zła komenda\r\n");
			}
		}
	}
}


