/*
 * timer.h
 *
 *  Created on: 8 paź 2026
 *      Author: cichy
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

extern volatile uint8_t game_tick;

void timer_init(void);

#endif /* TIMER_H_ */
