/*
 * ball.c
 *
 *  Created on: 11 paź 2026
 *      Author: cichy
 */
#include <stdint.h>
#include <stdio.h>

#include "ball.h"
#include "uart.h"

int16_t ball_x = 0;
int16_t ball_y = 0;
int16_t ball_vx = 0;
int16_t ball_vy = 0;

void ball_init(void){
	ball_x = 48;
	ball_y = 48;
	ball_vx = -1;
	ball_vy = -2;
}

static void ball_move_xy(void){
	ball_x += ball_vx;
	ball_y += ball_vy;
}

static void ball_bounce_x(void){
	if (ball_x <= (BALL_WIDTH/2) || ball_x >= BOARD_WIDTH-(BALL_WIDTH/2) ){
		ball_vx = - ball_vx;
	}
}

static void ball_bounce_y(void){
	if(ball_y <= (BALL_HEIGHT/2) || ball_y >= BOARD_HEIGHT-(BALL_WIDTH/2) ){
		ball_vy = - ball_vy;
	}
}

void ball_update(void){
	ball_move_xy();
	ball_bounce_x();
	ball_bounce_y();

	char buf[16];
	sprintf(buf, "BALL:%d,%d\r\n", ball_x, ball_y);
	uart_print(buf);
}



