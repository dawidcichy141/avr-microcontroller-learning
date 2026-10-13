/*
 * blocks.c
 *
 *  Created on: 12 paź 2026
 *      Author: cichy
 */
#include <stdio.h>
#include <stdint.h>
#include "blocks.h"
#include "ball.h"
#include "game.h"
#include "uart.h"

static void blocks_send_uart(void);
uint8_t blocks[BLOCK_ROWS][BLOCK_COLS];

void blocks_init(void){
	for(uint8_t i = 0; i < BLOCK_ROWS; i++){
		for (uint8_t j = 0; j < BLOCK_COLS; j++){
			blocks[i][j] = 1;
		}
	}
	blocks_send_uart();
}

uint8_t block_ball_collision(int16_t ball_x, int16_t ball_y, int16_t ball_vx, int16_t ball_vy){


//	if(ball_y >= BLOCK_BOTTOM_HEIGHT && (ball_x >= BLOCK_BOTTOM_WIDTH && ball_x <= BOARD_WIDTH - BLOCK_BOTTOM_WIDTH) && ball_y <= BLOCK_BOTTOM_HEIGHT + BLOCK_ROWS * BLOCK_HEIGHT){
//		uint8_t col = (ball_x - BLOCK_BOTTOM_WIDTH) / BLOCK_WIDTH;
//		uint8_t row = (ball_y - BLOCK_BOTTOM_HEIGHT) / BLOCK_HEIGHT;
	int16_t check_x;
	if (ball_vx > 0){
		check_x = ball_x + BALL_WIDTH;
	}
	else{
		check_x = ball_x;
	}
	int16_t check_y;
	if (ball_vy > 0) {
		check_y = ball_y + BALL_HEIGHT;
	} else {
		check_y = ball_y;
	}

	if(check_y >= BLOCK_BOTTOM_HEIGHT && check_y < BLOCK_BOTTOM_HEIGHT + BLOCK_ROWS * BLOCK_HEIGHT && check_x >= BLOCK_BOTTOM_WIDTH && check_x < BOARD_WIDTH - BLOCK_BOTTOM_WIDTH){
		uint8_t col = (check_x - BLOCK_BOTTOM_WIDTH) / BLOCK_WIDTH;
		uint8_t row = (check_y - BLOCK_BOTTOM_HEIGHT) / BLOCK_HEIGHT;
		if(blocks[row][col] == 1){
			blocks[row][col] = 0;
			blocks_send_uart();

			int16_t prev_x = check_x - ball_vx;
			int16_t block_left = BLOCK_BOTTOM_WIDTH + (col * BLOCK_WIDTH);
			int16_t block_right = block_left + BLOCK_WIDTH + BALL_WIDTH ;

			if(prev_x + BALL_WIDTH <= block_left || prev_x >= block_right){
				return 2;
			}
			else{
				return 1;
			}
		}
	}
	return 0;
}

static void blocks_destroyed(void){
	uint8_t win = 1;
	for(uint8_t i = 0; i < BLOCK_ROWS; i++){
		for(uint8_t j = 0; j < BLOCK_COLS; j++){
			if(blocks[i][j] == 1){
				win = 0;
				break;
			}
		}
		if(!win) break;
	}
	if(win){
		current_state = GAME_WIN;
	}
}

static void blocks_send_uart(void){
	char buf[BLOCK_ROWS * BLOCK_COLS + 10];
	uint8_t idx = 0;

	idx += sprintf(buf, "BLOCKS:");

		for (uint8_t i = 0; i < BLOCK_ROWS; i++){
			for(uint8_t j = 0; j < BLOCK_COLS; j++){

				buf[idx++] = blocks[i][j] ? '1' : '0';
			}
		}
		buf[idx++] = '\r';
		buf[idx++] = '\n';
		buf[idx] = '\0';

		uart_print(buf);
}


void block_update(void){
	blocks_destroyed();
}


