/*
 * main.c
 *
 *  Created on: 27 sie 2026
 *      Author: cichy
 */

#include <avr/io.h>
#include <util/delay.h>
//// Zadanie 1 Potencjometr kontrolujący miganie diody
//uint16_t adc_read(void){
//		ADCSRA |= (1<<ADSC);
//		while(ADCSRA & (1<<ADSC));
//		return ADC;
//	}
//
//int main(void){
//
//	ADMUX |= (1<<REFS0);
//
//	ADCSRA |= (1 << ADEN);
//	ADCSRA |= (1 << ADPS2);
//	ADCSRA |= (1 << ADPS1);
//
//	DDRC |= (1 << PC0);
//	PORTC |= (1<< PC0);
//
//
//	while(1){
//		int adc = adc_read();
//		PORTC ^= (1 << PC0);
//
//		for(uint16_t i = 0; i < adc; i++){
//					_delay_ms(1);
//				}
//
//	}
//}

//Zadanie 2  Wskaźnik Poziomu Napięcia

//uint16_t adc_read(void){
//	ADCSRA |= (1<< ADSC);
//	while(ADCSRA & (1<<ADSC));
//	return ADC;
//}
//
//int main(void){
//	DDRC |= (1 << PC0);
//	DDRC |= (1 << PC1);
//
//	PORTC |= (1 << PC0);
//	PORTC |= (1 << PC1);
//
//	ADMUX |= (1 << REFS0);
//
//	ADCSRA |= (1 << ADEN);
//	ADCSRA |= (1 << ADPS1);
//	ADCSRA |= (1 << ADPS2);
//
//	while(1){
//		int adc = adc_read();
//
//		if(adc <= 300){
//			PORTC &= ~(1 << PC0);
//			PORTC |= (1 << PC1);
//
//		}
//		else if (adc > 300 && adc <= 700){
//			PORTC &= ~(1 << PC0);
//			PORTC &= ~(1 << PC1);
//
//		}
//		else{
//			PORTC &= ~(1 << PC1);
//			PORTC |= (1 << PC0);
//		}
//		_delay_ms(100);
//	}
//
//}

// Zadanie 3 Prosty program z użyciem komparatora analogowego

//int main(void){
//	DDRC |= (1 << PC0);
//	PORTC |= (1 << PC0);
//
//
//	while(1){
//
//		if (ACSR & (1 << ACO)) {
//		    PORTC |= (1<< PC0);
//		} else {
//		    PORTC &= ~(1 << PC0);
//		}
//
//	}
//}

// Zadanie 4 Komparator + Wewnętrzne Napięcie Odniesienia (Bandgap 1,23 V)
//int main(void){
//	DDRC |= (1 << PC0);
//	PORTC |= (1 << PC0);
//
//	ACSR |= (1 << ACBG);
//
//	while(1){
//
//		if (ACSR & (1 << ACO)) {
//		    PORTC |= (1<< PC0);
//		} else {
//		    PORTC &= ~(1 << PC0);
//		}
//
//	}
//}



