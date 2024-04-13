/**
 ******************************************************************************
 * @file    API_Delay.c.
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   This file implements a non blocking delay hanging timer tick
 *
 ******************************************************************************
 **/
/* Private functions --------------------------------------------------------- */
#include "API_Delay.h"

/* Priavete Declarate functions ---------------------------------------------- */
static void delayError_Handler(void);

/**
 * func    delayInit
 * @brief  Initialize a delay
 * @param  delay_t, tick_t
 * @retval None
 */
void delayInit(delay_t *delay, tick_t duration) {

	if (delay != NULL) {

		if ((0 < duration) && (duration <= DELAY_MAX)) {

			delay->duration = duration;
			delay->running = false;

		}
	}
	else{

		delayError_Handler();

	}

	return;
}

/**
 * @func   delayRead
 * @brief  read and check timer tick delay
 * @param  delay_t
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
	else{

		delayError_Handler();

	}

	return stts;
}

/**
 * @func   delayWrite
 * @brief  Change duration timer tick delay
 * @param  delay_t struct, tick_t
 * @retval None
 */
void delayWrite(delay_t *delay, tick_t duration) {

	if (delay != NULL) {

		if ((!delay->running) && (0 < duration) && (duration <= DELAY_MAX)) {

			delay->duration = duration;

		}

	}
	else{

		delayError_Handler();

	}

	return;
}

/**
 * @func   delayError_Handler
 * @brief  Catch an error
 * @param  None
 * @retval None
 */
static void delayError_Handler(void){
	while(1){

	}
}
