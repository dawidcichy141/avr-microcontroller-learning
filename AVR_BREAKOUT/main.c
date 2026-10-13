/*
 * main.c
 *
 *  Created on: 8 paź 2026
 *      Author: cichy
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "game.h"
#include "timer.h"
#include "uart.h"
#include "paddle.h"
#include "ball.h"
#include "blocks.h"

int main(void){
	DDRC |= (1 << PC7);
	timer_init();

	sei();

	uart_init(115200UL);
	paddle_init();
	ball_init();
	blocks_init();

	char command = 0;
	while(1){

		char cmd = uart_reciver();
		if(cmd != 0){
			command = cmd;
		}

		if(game_tick){
			game_tick = 0;
			if(current_state == GAME_RUNNING){
				paddle_update(command);
				ball_update();
				block_update();
			}
			update_game(command);
			command = 0;
		}
	}
}

