/*
 * main.c
 *
 *  Created on: 28 lip 2026
 *      Author: cichy
 */

#include <avr/io.h>
#include <util/delay.h>

//PRZYKŁAD:
//int main(void) {
//    // 1. Konfiguracja kierunku (DDR)
//    DDRC |= (1 << PC0);   // PB0 jako WYJŚCIE (LED)
//    DDRD &= ~(1 << PD2);  // PD2 jako WEJŚCIE (Przycisk)
//
//    // 2. Konfiguracja stanu początkowego / Pull-up (PORT)
//    PORTD |= (1 << PD2);  // Włączenie wewnętrznego rezystora pull-up na PD2
//
//    while (1) {
//        // Sprawdzamy czy przycisk na PD2 został wciśnięty (zwarty do masy / stan 0)
//        if (!(PIND & (1 << PD2))) {
//            PORTC |= (1 << PC0);  // Włącz LED na PB0 (stan wysoki)
//        } else {
//            PORTC &= ~(1 << PC0); // Wyłącz LED na PB0 (stan niski)
//        }
//    }
//
//    return 0;
//}

//ZADANIE 1 Zapalanie 4 diód przyciskiem

//int main(void) {
//    DDRC = 0xFF;
//    PORTC = 0xFF;
//
//    DDRA &= ~(1 << PA3);
//    PORTA |= (1 << PA3);
//
//    while (1) {
//        if (!(PINA & (1 << PA3))) {
//            PORTC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3));
//        } else {
//            PORTC = 0xFF;
//        }
//    }
//
//    return 0;
//}

//ZADANIE 2 Tryb przełącznika

//int main(void){
//
//	DDRC |= (1 << PC0);
//	PORTC |= (1 << PC0);
//
//	DDRA &= ~(1 << PA3);
//	PORTA |= (1<< PA3);
//
//	while(1){
//		if (!(PINA & (1 << PA3))){
//			_delay_ms(30);
//			if  (PINC & (1 << PC0)) {
//				PORTC &= ~(1 << PC0);
//			}
//			else{
//				PORTC |= (1 << PC0);
//			}
//			while(!(PINA & (1<<PA3))){
//
//			}
//			_delay_ms(30);
//
//		}
//	}
//
//}
//ZADANIE 3 WĘŻYK DIODOWY

//int main(void){
//	DDRC |= ((1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3));
//	PORTC = 0xFF;
//
//	while(1){
//		for (uint8_t i=0; i<4; i++){
//			PORTC = ~(1<<i);
//			_delay_ms(10000);
//		}
//
//		for (int8_t i=2;i>0;i--){
//			PORTC = ~(1<<i);
//			_delay_ms(10000);
//
//		}
//	}
//}




