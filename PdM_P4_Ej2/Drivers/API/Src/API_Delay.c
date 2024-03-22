/**
 ******************************************************************************
 * @file    API/Inc/API_Delay.c.
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   PdM - Practical Work 4 - Exercise 2
 * 		 	This file implements non blocking delay hanging timer tick
 ******************************************************************************
 **/
/* Private functions --------------------------------------------------------- */
#include "API_Delay.h"

/**
 * @brief  delayInit function initialize a delay
 * @param  delay_t struct, tick_t
 * @retval None
 */
void delayInit(delay_t *delay, tick_t duration) {
	if (delay != NULL) {
		if ((0 < duration) && (duration <= DELAY_MAX)) {
			delay->duration = duration;
			delay->running = false;
		}
	}
}

/**
 * @func   delayRead
 * @brief  read and check timer tick delay
 * @param  delay_t struct
 * @retval bool_t
 */
bool_t delayRead(delay_t *delay) {

	bool_t stts = false;
	tick_t get_tick = 0;

	if (delay != NULL) {
		get_tick = HAL_GetTick();
		if (delay->running) {
			if ((get_tick - delay->startTime) >= delay->duration) {
				delay->running = false;
				stts = true;
			}
		} else {
			delay->startTime = get_tick;
			delay->running = true;
		}
	}
	return stts;
}

/**
 * @func   delayWrite
 * @brief  change duration timer tick delay
 * @param  delay_t struct, tick_t
 * @retval None
 */
void delayWrite(delay_t *delay, tick_t duration) {
	if (delay != NULL) {
		if ((!delay->running) && (0 < duration) && (duration <= DELAY_MAX)) {
			delay->duration = duration;
		}
	}
}
