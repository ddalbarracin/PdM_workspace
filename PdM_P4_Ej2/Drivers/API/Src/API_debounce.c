/**
 ******************************************************************************
 * @file    API_debounce.c
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   PdM - Practical Work 4 - Exercise 2
 * 		 	This file implements a Finite State Machine functions
 *
 ******************************************************************************
 **/
/* Includes ------------------------------------------------------------------ */
#include "API_debounce.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"



/* Private typedef -----------------------------------------------------------*/
/* Button State enum */
typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RISING,
} debounceState_t;

/* Private variables ---------------------------------------------------------*/
static debounceState_t ActualState;
static delay_t button_delay;
static Led_TypeDef led[] = { LED_GREEN, LED_BLUE, LED_RED };
static Button_TypeDef button = BUTTON_USER;
bool_t frec_flg;

/* Private Functions */
/*
 * @func   buttonPressed
 * @brief  Press Button event
 * @param  button_t
 * @retval None
 */
static void buttonPressed(void) {
	/*uint8_t led_indx, led_size;
	led_size = sizeof(led) / sizeof(Led_TypeDef);
	for (led_indx = 0; led_indx < led_size; led_indx++) {
			BSP_LED_On(led[led_indx]);
		}*/
	frec_flg = true;
	return;
}

/*
 * @func   debounceFSM_init
 * @brief  Initialize FSM
 * @param  None
 * @retval None
 */
void debounceFSM_init(void) {
	ActualState = BUTTON_UP;
	return;
}
/*
 * @func   debounceFSM_update
 * @brief  Initialize FSM
 * @param  None
 * @retval None
 */
void debounceFSM_update(void) {

	switch (ActualState) {
	case BUTTON_UP:
		if (BSP_PB_GetState(button)) {
			delayInit(&button_delay, UPTOFALL);
			ActualState = BUTTON_FALLING;
		}
		break;
	case BUTTON_FALLING:
		if (delayRead(&button_delay)) {
			if (BSP_PB_GetState(button)) {
				buttonPressed();
				ActualState = BUTTON_DOWN;
			} else {
				ActualState = BUTTON_UP;
			}
		}
		break;
	case BUTTON_DOWN:
		if (!BSP_PB_GetState(button)) {
			delayInit(&button_delay, RISETODOWN);
			ActualState = BUTTON_RISING;

		}
		break;
	case BUTTON_RISING:
		if (delayRead(&button_delay)) {
			if (!BSP_PB_GetState(button)) {
				ActualState = BUTTON_UP;
			} else {
				ActualState = BUTTON_DOWN;
			}
		}
		break;
	default:
		debounceFSM_init();
		break;
	}
	return;
}


bool_t readKey(void) {

	bool_t stts = false;

	if (frec_flg) {
		stts = frec_flg;
		frec_flg = false;
	}

	return (stts);
}

