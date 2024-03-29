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


/* Private variables ---------------------------------------------------------*/
static debounceState_t ActualState;
static delay_t button_delay;
static Button_TypeDef button = BUTTON_USER;
static bool_t btnPress;
static bool_t btnReleas;

/* Private Functions */
/*
 * @func   buttonPressed
 * @brief  Press Button event
 * @param  None
 * @retval None
 */
static void buttonPressed(void) {
	btnPress = true;
	return;
}

/*
 * @func   buttonReleased
 * @brief  Released Button event
 * @param  None
 * @retval None
 */
static void buttonReleased(void){
	btnReleas = true;
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
	btnPress = false;
	btnReleas = false;
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
				buttonReleased();
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
/*
 * @func   readKey
 * @brief  signal API module to check falling
 *         and rising edge of user button
 * @param  uint8_t state
 * @retval bool_t
 */
bool_t readKey(uint8_t state) {

	bool_t stts = false;
	if( state == BUTTON_FALLING){
		if (btnPress) {
			stts = btnPress;
			btnPress = false;
		}
	}
	if (state == BUTTON_RISING){
		if (btnReleas) {
			stts = btnReleas;
			btnReleas = false;
		}
	}

	return (stts);
}

