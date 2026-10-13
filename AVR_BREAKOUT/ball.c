/*
 * ball.c
 *
 *  Created on: 11 paź 2026
 *      Author: cichy
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "ball.h"
#include "uart.h"
#include "paddle.h"
#include "game.h"
#include "blocks.h"

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
	if(ball_y >= BOARD_HEIGHT-(BALL_HEIGHT/2) ){
		ball_vy = - abs(ball_vy);
	}
}


static void ball_bounce_paddle(void){
	if(ball_vy < 0 && ball_y <= (paddle_y + PADDLE_HEIGHT) && ball_y >= paddle_y){
		if (ball_x + BALL_WIDTH >= paddle_x && ball_x <= (paddle_x + PADDLE_WIDTH)){
			ball_vy = abs(ball_vy);
			ball_y = paddle_y + PADDLE_HEIGHT + 1;
		}
	}
}

static void game_over(void){
	if (ball_y <= 0){
		current_state = GAME_OVER;
	}

}

static void ball_bounce_block(void){
	uint8_t hit = block_ball_collision(ball_x,ball_y,ball_vx,ball_vy);

	if(hit == 1){
		ball_vy = -ball_vy;
	}
	else if(hit == 2){
		ball_vx = -ball_vx;
	}
}


void ball_update(void){

	static uint8_t tick_counter = 0;
	tick_counter++;
	if(tick_counter % 3 ==0){
		ball_move_xy();
		ball_bounce_x();
		ball_bounce_y();
		ball_bounce_paddle();
		ball_bounce_block();
		game_over();
	}

	char buf[16];
	sprintf(buf, "BALL:%d,%d\r\n", ball_x, ball_y);
	uart_print(buf);
}



