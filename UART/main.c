/*
 * main.c
 *
 *  Created on: 28 sie 2026
 *      Author: cichy
 */
//Przyklad
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#define BAUDRATE 9600
#define MYUBRR ((F_CPU / (16UL * BAUDRATE)) - 1)

//void uart_init(unsigned int ubrr) {
//    UBRRH = (unsigned char)(ubrr >> 8);
//    UBRRL = (unsigned char)ubrr;
//
//    UCSRB = (1 << RXEN) | (1 << TXEN);
//    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
//}
//
//void uart_putc(char data) {
//    while (!(UCSRA & (1 << UDRE)));
//    UDR = data;
//}
//
//void uart_puts(const char *s) {
//    while (*s) {
//        uart_putc(*s++);
//    }
//}
//
//char uart_getc(void) {
//    while (!(UCSRA & (1 << RXC)));
//    return UDR;
//}
//
//int main(void) {
//    uart_init(MYUBRR);
//
//    _delay_ms(100);
//
//    uart_puts("\r\n-------------------------\r\n");
//    uart_puts("   ATmega32 @ 8MHz OK!   \r\n");
//    uart_puts("   Baudrate: 9600        \r\n");
//    uart_puts("-------------------------\r\n");
//    uart_puts("Wpisz cos z klawiatury: ");
//
//    while (1) {
//        // Odbierz znak i natychmiast go wyślij (Echo)
//        char received = uart_getc();
//        uart_putc(received);
//    }
//}



//Zadanie 1 Odpalanie diody z poziomu klawiatury
//void uart_init(unsigned int ubrr){
//	UBRRH = (unsigned char)(ubrr >> 8);
//	UBRRL = (unsigned char)ubrr;
//
//	UCSRB |= (1 << TXEN);
//	UCSRB |= (1 << RXEN);
//
//	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
//
//
//}
//
//void uart_putc(unsigned char data){
//	while(!(UCSRA & (1 << UDRE))){
//
//	}
//	UDR = data;
//}
//
//void uart_puts(const char *s){
//	while(*s){
//		uart_putc(*s++);
//
//	}
//
//}
//
//char uart_getc(void) {
//    while (!(UCSRA & (1 << RXC)));
//    return UDR;
//}
//
//int main(void){
//	uart_init(MYUBRR);
//
//	uart_puts("\r\n-------------------------\r\n");
//	uart_puts("   ATmega32 @ 8MHz OK!   \r\n");
//	uart_puts("   Baudrate: 9600        \r\n");
//	uart_puts("-------------------------\r\n");
//	uart_puts("Wpisz cos z klawiatury: ");
//
//	DDRC |= (1 << PC0);
//
//
//
//
//	while(1){
//		int received = 0;
//		received = uart_getc();
//
//		if(received == '1'){
//			PORTC &= ~(1 << PC0);
//			uart_puts("\r\nZapalono diode\r\n");
//		}
//		else if(received == '0'){
//			PORTC |= (1 << PC0);
//			uart_puts("\r\nZgaszono diode\r\n");
//		}
//		else{
//			uart_puts("\r\nZly format danych\r\n");
//		}
//
//
//
//	}
//}
//Zadanie 2 Komendy tekstowe

//void uart_init(unsigned int ubrr){
//	UBRRH = (unsigned char)(ubrr >> 8);
//	UBRRL = (unsigned char)ubrr;
//
//	UCSRB |= (1 << TXEN);
//	UCSRB |= (1 << RXEN);
//
//	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
//
//
//}
//
//void uart_putc(unsigned char data){
//	while(!(UCSRA & (1 << UDRE))){
//
//	}
//	UDR = data;
//}
//
//void uart_puts(const char *s){
//	while(*s){
//		uart_putc(*s++);
//
//	}
//
//}
//
//char uart_getc(void) {
//    while (!(UCSRA & (1 << RXC)));
//    return UDR;
//}
//
//void uart_gets(char *buffer , uint8_t max_len){
//	uint8_t i = 0;
//	char komenda;
//
//	while(1){
//		komenda = uart_getc();
//
//		if(komenda == '\r' || komenda == '\n'){
//			buffer[i] = '\0';
//			break;
//		}
//		if (i < max_len-1){
//			buffer[i] = komenda;
//			i++;
//			uart_putc(komenda);
//		}
//	}
//}
//
//
//int main(void){
//	uart_init(MYUBRR);
//
//	uart_puts("\r\n-------------------------\r\n");
//	uart_puts("   ATmega32 @ 8MHz OK!   \r\n");
//	uart_puts("   Baudrate: 9600        \r\n");
//	uart_puts("-------------------------\r\n");
//	uart_puts("Wpisz cos z klawiatury: ");
//
//	DDRC |= (1 << PC0);
//
//
//	char komenda[16];
//
//	while(1){
//		uart_gets(komenda, sizeof(komenda));
//
//
//		        if (strcmp(komenda, "ON") == 0) {
//		            PORTC &= ~(1 << PC0);
//		            uart_puts("\r\nDioda wlaczona!\r\n");
//		        }
//		        else if (strcmp(komenda, "OFF") == 0) {
//		            PORTC |= (1 << PC0);
//		            uart_puts("\r\nDioda wylaczona\r\n");
//		        }
//		        else {
//		            uart_puts("\r\n Nieznana komenda\r\n");
//		        }
//	}
//}

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
    while (!(UCSRA & (1 << RXC)));
    return UDR;
}

void print_menu(void) {
    uart_puts("\r\n--- MENU ATmega32 ---\r\n");
    uart_puts(" 1 - Zapal LED\r\n");
    uart_puts(" 0 - Zgas LED\r\n");
    uart_puts(" s - Pokaz status LED\r\n");
    uart_puts(" m - Wyswietl menu\r\n");
    uart_puts("---------------------\r\n");
}

int main(void){
	DDRC |= (1 << PC0);
	PORTC |= (1 << PC0);

	uart_init(MYUBRR);
	_delay_ms(100);

	print_menu();

	while(1){
		char c = uart_getc();

		        switch (c) {
		            case '1':
		                PORTC &= ~(1 << PC0);
		                uart_puts("\r\nDiodka zapalona\r\n");
		                break;

		            case '0':
		                PORTC |= (1 << PC0);
		                uart_puts("\r\nDiodka zgaszona\r\n");
		                break;

		            case 's':
		            case 'S':
		                if(!(PINC & (1<<PC0))){
		                	uart_puts("\r\nStatus diodki: Zapalona\r\n");
		                }
		                else{
		                	uart_puts("\r\nStatus diodki: Zgaszona\r\n");
		                }

		                break;

		            case 'm':
		            case 'M':
		                print_menu();
		                break;

		            default:
		                uart_puts("\r\nNieznana opcja! Wpisz 'm' aby zobaczyc menu.\r\n");
		                break;

		        }
	}
}


