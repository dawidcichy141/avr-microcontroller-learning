/*
 * paddle.c
 *
 *  Created on: 11 paź 2026
 *      Author: cichy
 */
#include <stdio.h>

#include "paddle.h"
#include "uart.h"

uint16_t paddle_x = 0;

void paddle_init(void){
	paddle_x = 40;
}

static void move_paddle_left(char command){
	if(command == 'a'){
		if(paddle_x > 0){
			paddle_x = paddle_x - 2;
		}
	}
}

static void move_paddle_right(char command){
	if(command == 'd'){
		if(paddle_x < BOARD_WIDTH - PADDLE_WIDTH){
			paddle_x = paddle_x + 2;
		}
	}

}

void paddle_update(char command){

	move_paddle_right(command);
	move_paddle_left(command);
	char buf[16];
	sprintf(buf, "PADDLE:%d\r\n", paddle_x);
	uart_print(buf);
}
