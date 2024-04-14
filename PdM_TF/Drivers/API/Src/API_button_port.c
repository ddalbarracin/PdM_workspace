/**
 ******************************************************************************
 * @file    API_button_port.c
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   This file make an interface between Button and GPIO Hardware
 *
 ******************************************************************************
 */
/* includes  ----------------------------------------------------------------*/
#include "API_button_port.h"
#include "API_gpio.h"

/* Global Variables ---------------------------------------------------------*/
static Button_st ptrButton[PB_PORT_QTY];

/* Private Prototype Functions ----------------------------------------------*/
static void btnPortError_Handler(_Bool);

/* Functions ----------------------------------------------------------------*/
/*
 * @func   PB_PORT_Init
 * @brief
 * @param  uint8_t
 * @retval _Bool
 */
_Bool PB_PORT_Init(uint8_t button) {

	_Bool stts = false;
	Button_st btn;

	btn.index = button;
	btn.mode = PB_PORT_MODE;
	btn.pull = PB_PORT_PULL;
	btn.speed = PB_PORT_SPEED;

	if (button == BUTTON_UP) {
		btn.pin = PB_PORT_UP_PIN;
		btn.port = PB_PORT_UP_PORT;
	}
	if (button == BUTTON_DOWN) {

		btn.pin = PB_PORT_DOWN_PIN;
		btn.port = PB_PORT_DOWN_PORT;

	}
	if (button == BUTTON_ENTER) {

		btn.pin = PB_PORT_ENTER_PIN;
		btn.port = PB_PORT_ENTER_PORT;

	}
	if (button == BUTTON_BACK) {

		btn.pin = PB_PORT_BACK_PIN;
		btn.port = PB_PORT_BACK_PORT;

	}

	stts = GPIO_Init(&btn);
	if (stts != true) {

		btnPortError_Handler(stts);

	} else {

		ptrButton[button] = btn;

	}

	return (stts);

}

/*
 * @func   PB_PORT_GetState
 * @brief  Get State of Button
 * @param  uint8_t
 * @retval GPIO_PinState
 */
GPIO_PinState PB_PORT_GetState(uint8_t button) {

	GPIO_PinState pbStatus;

	pbStatus = GPIO_GetState(&ptrButton[button]);

	return (pbStatus);

}

/*
 * @func   PB_PORT_DeInit
 * @brief  DeInitialize button
 * @param  uint8_t
 * @retval _Bool
 */
_Bool PB_PORT_DeInit(uint8_t button) {

	_Bool stts = false;
	Button_st btn;

	btn.index = button;
	btn.mode = PB_PORT_MODE;
	btn.pull = PB_PORT_PULL;
	btn.speed = PB_PORT_SPEED;

	if (button == BUTTON_UP) {

		btn.pin = PB_PORT_UP_PIN;
		btn.port = PB_PORT_UP_PORT;

	}
	if (button == BUTTON_DOWN) {

		btn.pin = PB_PORT_DOWN_PIN;
		btn.port = PB_PORT_DOWN_PORT;

	}
	if (button == BUTTON_ENTER) {
		btn.pin = PB_PORT_ENTER_PIN;
		btn.port = PB_PORT_ENTER_PORT;

	}
	if (button == BUTTON_BACK) {

		btn.pin = PB_PORT_BACK_PIN;
		btn.port = PB_PORT_BACK_PORT;

	}

	stts = GPIO_DeInit(&btn);

	if (stts != true) {

		btnPortError_Handler(stts);

	}

	return (stts);

}

/*
 * @func   btnPortError_Handler
 * @brief  Press Button event
 * @param  _Bool
 * @retval None
 */
static void btnPortError_Handler(_Bool) {
	while (1) {

	}
}

