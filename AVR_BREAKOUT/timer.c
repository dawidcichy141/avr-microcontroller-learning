/*
 * timer.c
 *
 *  Created on: 8 paź 2026
 *      Author: cichy
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

volatile uint8_t game_tick = 0;

void timer_init(void){

	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS12) | (1 << CS10);

	OCR1A = 107;

	TIMSK |= (1 << OCIE1A);
}


ISR(TIMER1_COMPA_vect){
	game_tick = 1;
}
