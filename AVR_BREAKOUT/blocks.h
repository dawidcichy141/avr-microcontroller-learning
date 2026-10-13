/*
 * blocks.h
 *
 *  Created on: 12 paź 2026
 *      Author: cichy
 */

#ifndef BLOCKS_H_
#define BLOCKS_H_

#include <stdint.h>

#define BOARD_WIDTH 100
#define BOARD_HEIGHT 100
#define BLOCK_ROWS 4
#define BLOCK_COLS 7
#define BLOCK_WIDTH 12
#define BLOCK_HEIGHT 4
#define BLOCK_BOTTOM_HEIGHT 70
#define BLOCK_BOTTOM_WIDTH 8

extern uint8_t blocks[BLOCK_ROWS][BLOCK_COLS];

void blocks_init(void);
uint8_t block_ball_collision(int16_t ball_x, int16_t ball_y,int16_t ball_vx, int16_t ball_vy);
void block_update(void);


#endif /* BLOCKS_H_ */
