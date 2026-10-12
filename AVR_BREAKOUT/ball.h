/*
 * ball.h
 *
 *  Created on: 11 paź 2026
 *      Author: cichy
 */

#ifndef BALL_H_
#define BALL_H_
#include <stdint.h>

#define BOARD_WIDTH 100
#define BOARD_HEIGHT 100
#define BALL_WIDTH 4
#define BALL_HEIGHT 4

extern int16_t ball_x;
extern int16_t ball_y;
extern int16_t ball_vx;
extern int16_t ball_vy;

void ball_init(void);
void ball_update(void);


#endif /* BALL_H_ */
