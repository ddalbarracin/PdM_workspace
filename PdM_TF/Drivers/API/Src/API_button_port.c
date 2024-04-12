/**
 ******************************************************************************
 * @file    API/Inc/API_button_port.c
 * @author  Daniel David Albarracin
 * @brief   File to Access to Hardware by API_gio.c
 ******************************************************************************
 */
/* includes  -----------------------------------------------------------------*/
#include "API_button_port.h"
#include "API_gpio.h"

/* Global Variables ------------------------------------------------------------------------*/
static Button_st ptrButton[4];
/* Private Prototype Functions ------------------------------------------------------------ */
static void btnPortError_Handler(_Bool);

/* Functions ------------------------------------------------------------ ------------------*/

/*
 * @func   PB_PORT_Init
 * @brief
 * @param  uint8_t
 * @retval _Bool
 */
_Bool PB_PORT_Init(uint8_t button){

	_Bool stts = false;
	Button_st btn;

	btn.index = button;
	btn.mode = PButton_MODE;
	btn.pull = PButton_PULL;
	btn.speed = PButton_SPEED;

	if (button == BUTTON_UP) {
		btn.pin = PButton_UP_PIN;
		btn.port = PButton_UP_PORT;
	}
	if (button == BUTTON_DOWN) {
		btn.pin = PButton_DOWN_PIN;
		btn.port = PButton_DOWN_PORT;
	}
	if (button == BUTTON_ENTER) {
		btn.pin = PButton_ENTER_PIN;
		btn.port = PButton_ENTER_PORT;
	}
	if (button == BUTTON_BACK) {
		btn.pin = PButton_BACK_PIN;
		btn.port = PButton_BACK_PORT;
	}

	stts = GPIO_Init(&btn);
	if (stts != true){
		btnPortError_Handler(stts);

	}else{
		ptrButton[button] = btn;
	}
	return(stts);
}

/*
 * @func   PB_PORT_GetState
 * @brief  Press Button event
 * @param  uint8_t
 * @retval _Bool
 */
GPIO_PinState PB_PORT_GetState(uint8_t button){

	GPIO_PinState pbStatus;

	pbStatus = GPIO_GetState(&ptrButton[button]);

	return(pbStatus);
}

/*
 * @func   PB_PORT_DeInit
 * @brief  Press Button event
 * @param  uint8_t
 * @retval _Bool
 */
_Bool PB_PORT_DeInit(uint8_t button){

	_Bool stts = false;
	Button_st btn;

	btn.index = button;
	btn.mode = PButton_MODE;
	btn.pull = PButton_PULL;
	btn.speed = PButton_SPEED;

	if (button == BUTTON_UP) {
		btn.pin = PButton_UP_PIN;
		btn.port = PButton_UP_PORT;
	}
	if (button == BUTTON_DOWN) {
		btn.pin = PButton_DOWN_PIN;
		btn.port = PButton_DOWN_PORT;
	}
	if (button == BUTTON_ENTER) {
		btn.pin = PButton_ENTER_PIN;
		btn.port = PButton_ENTER_PORT;
	}
	if (button == BUTTON_BACK) {
		btn.pin = PButton_BACK_PIN;
		btn.port = PButton_BACK_PORT;
	}

	stts = GPIO_DeInit(&btn);
	if (stts != true){
		btnPortError_Handler(stts);

	}
	return(stts);
}

/*
 * @func   btnPortError_Handler
 * @brief  Press Button event
 * @param  _Bool
 * @retval None
 */
static void btnPortError_Handler(_Bool){
	while(1){

	}
}

