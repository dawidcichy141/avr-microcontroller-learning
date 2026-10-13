/*
 * paddle.h
 *
 *  Created on: 11 paź 2026
 *      Author: cichy
 */

#ifndef PADDLE_H_
#define PADDLE_H_
#define BOARD_WIDTH 100
#define PADDLE_WIDTH 20
#define PADDLE_HEIGHT 2
#include <stdint.h>

extern uint16_t paddle_x;
extern uint16_t paddle_y;

void paddle_init(void);
void paddle_update(char command);

#endif /* PADDLE_H_ */
