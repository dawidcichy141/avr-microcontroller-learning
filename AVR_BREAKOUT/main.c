/*
 * main.c
 *
 *  Created on: 8 paź 2026
 *      Author: cichy
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "game.h"
#include "timer.h"


int main(void){
	DDRC |= (1 << PC7);
	timer_init();

	sei();

	while(1){

		if(game_tick){
			game_tick = 0;

			update_game();
		}
	}
}

