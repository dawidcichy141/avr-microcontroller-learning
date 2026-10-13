/*
 * game.c
 *
 *  Created on: 8 paź 2026
 *      Author: cichy
 */
#include <stdio.h>

#include "game.h"
#include "uart.h"
#include "blocks.h"
#include "ball.h"
#include "paddle.h"

GameState current_state = GAME_MENU;
static GameState last_sent_state = 255;

void update_game(char cmd){


	if (current_state != last_sent_state) {
	        last_sent_state = current_state;
	        char buf[20];
	        sprintf(buf, "STATE:%d\r\n", (int)current_state);
	        uart_print(buf);
	    }
	switch (current_state){
	case GAME_MENU:
		if(cmd == 's'){
			current_state = GAME_RUNNING;
		}
		break;
	case GAME_RUNNING:
		if(cmd == 'p'){
			current_state = GAME_PAUSED;
		}
		break;
	case GAME_PAUSED:
		if(cmd == 's'){
			current_state = GAME_RUNNING;
		}
		if(cmd == 'r'){
			reset_game();
			current_state = GAME_MENU;
		}
		break;
	case GAME_OVER:
		if(cmd == 'r'){
			reset_game();
			current_state = GAME_MENU;
		}
		break;
	case GAME_WIN:
		if(cmd == 'r'){
			reset_game();
			current_state = GAME_MENU;
		}
		break;
	default:
		current_state = GAME_MENU;
		break;
	}
}

void reset_game(void){
	paddle_init();
	ball_init();
	blocks_init();
	current_state = GAME_MENU;
}

