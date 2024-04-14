/**
 ******************************************************************************
 * @file    API_gpio.c
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   File to manage GPIO hardware module
 *
 ******************************************************************************
 */
/* includes -----------------------------------------------------------------*/
#include "API_gpio.h"

/* Private Functions --------------------------------------------------------*/
/*
 * @func   GPIO_Init
 * @brief  Initialize GPIO
 * @param  Button_st
 * @retval _Bool
 */
_Bool GPIO_Init(Button_st *ptr_button) {

	GPIO_InitTypeDef GPIO_InitStruct;
	_Bool stts = false;

	if (ptr_button != NULL) {
		/* Enable the BUTTON Clock */
		PButton_GPIO_PORT_CLK_ENABLE(ptr_button->port);

		if (ptr_button->mode == GPIO_MODE_INPUT) {
			/* Configure Button pin as input */
			GPIO_InitStruct.Pin = ptr_button->pin;
			GPIO_InitStruct.Mode = ptr_button->mode;
			GPIO_InitStruct.Pull = ptr_button->pull;
			GPIO_InitStruct.Speed = ptr_button->speed;
			HAL_GPIO_Init(ptr_button->port, &GPIO_InitStruct);

		}
		stts = true;
	}

	return (stts);

}

/*
 * @func   GPIO_GetState
 * @brief  Read GPIO State
 * @param  Button_st
 * @retval GPIO_PinState
 */
GPIO_PinState GPIO_GetState(Button_st *ptr_button) {

	GPIO_PinState gpioState;

	if (ptr_button != NULL) {

		gpioState = HAL_GPIO_ReadPin(ptr_button->port, ptr_button->pin);
	}

	return (gpioState);

}

/*
 * @func   GPIO_DeInit
 * @brief  DeInit GPIOs
 * @param  Button_st
 * @retval _Bool
 */
_Bool GPIO_DeInit(Button_st *ptr_button) {

	_Bool stts = false;

	if (ptr_button != NULL) {

		PButton_GPIO_PORT_CLK_DISABLE(ptr_button->port);
		HAL_GPIO_DeInit(ptr_button->port, ptr_button->pin);
		stts = true;

	}

	return (stts);

}
