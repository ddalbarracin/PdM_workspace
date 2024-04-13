/**
 ******************************************************************************
 * @file    API_Delay.h
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   Header for API_Delay.c
 *
 ******************************************************************************
 */
/* include guard -------------------------------------------------------------*/
#ifndef API_DELAY
#define API_DELAY
/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"

/* Typedef  ------------------------------------------------------------------*/
typedef uint32_t tick_t;
typedef _Bool bool_t;

typedef struct {
	tick_t startTime;
	tick_t duration;
	bool_t running;
} delay_t;

/* Exported constants --------------------------------------------------------*/
#define DELAY 			100  			// Base Period
#define DELAY_MAX 		(DELAY*100)
#define PERIOD_500 		(DELAY*5)
#define PERIOD_400 		(DELAY*4)
#define PERIOD_300 		(DELAY*3)
#define PERIOD_200 		(DELAY*2)
#define PERIOD_100 		(DELAY*1)
#define PERIOD_0   		(DELAY*0)
#define SEQUENCY 		6

/* Exported functions ------------------------------------------------------- */
void delayInit(delay_t *delay, tick_t duration);
bool_t delayRead(delay_t *delay);
void delayWrite(delay_t *delay, tick_t duration);


#endif /* API_DELAY */
