/*
 * project1.c
 *
 *  Created on: 27 sie 2026
 *      Author: cichy
 */
#include <avr/io.h>
#include <util/delay.h>
// Prowizoryczny czujnik parkowania z uzyciem czujnika ultradzwiekowego (US-105)

int main(void){

	DDRC |= (1 << PC0);
	PORTC |= (1 << PC0);

	DDRC |= (1<< PC1);
	DDRC &= ~(1 << PC2);




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
		for (int i = 0; i < distance; i++){
			_delay_ms(1);
		}

		_delay_ms(50);
	}
}


