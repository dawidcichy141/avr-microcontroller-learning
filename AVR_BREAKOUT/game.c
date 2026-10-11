/*
 * game.c
 *
 *  Created on: 8 paź 2026
 *      Author: cichy
 */


#include "game.h"

GameState current_state = GAME_MENU;

void update_game(void){
	switch (current_state){
	case GAME_MENU:
		break;
	case GAME_RUNNING:
		break;
	case GAME_PAUSED:
		break;
	case GAME_OVER:
		break;
	case GAME_WIN:
		break;
	default:
		current_state = GAME_MENU;
		break;
	}
}

