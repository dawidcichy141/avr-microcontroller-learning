/*
 * game.h
 *
 *  Created on: 8 paź 2026
 *      Author: cichy
 */

#ifndef GAME_H_
#define GAME_H_

//Definicja możliwych stanów gry
typedef enum{
	GAME_MENU,
	GAME_RUNNING,
	GAME_PAUSED,
	GAME_OVER,
	GAME_WIN
} GameState;

extern GameState current_state;

void update_game(void);


#endif /* GAME_H_ */
