/**
 ******************************************************************************
 * @file    API/Inc/API_button_port.h
 * @author  Daniel David Albarracin
 * @brief   Header of API_button_port.c
 ******************************************************************************
 */
/* includes  guard-----------------------------------------------------------------*/
#ifndef API_BUTTON_PORT
#define API_BUTTON_PORT
/* includes  -----------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "API_button.h"
#include "stm32f4xx_hal.h"

/* Defines  -----------------------------------------------------------------*/
#define PButton_MODE 				GPIO_MODE_INPUT
#define PButton_PULL 				GPIO_NOPULL
#define PButton_SPEED 				GPIO_SPEED_FAST

#define PButton_UP_PIN				GPIO_PIN_12
#define PButton_DOWN_PIN			GPIO_PIN_13
#define PButton_ENTER_PIN			GPIO_PIN_1
#define PButton_BACK_PIN			GPIO_PIN_0

#define PButton_UP_PORT				GPIOF
#define PButton_DOWN_PORT			GPIOF
#define PButton_ENTER_PORT			GPIOG
#define PButton_BACK_PORT			GPIOG


typedef struct {
	uint8_t index;
	uint32_t pin;
	uint32_t mode;
	uint32_t pull;
	uint32_t speed;
	GPIO_TypeDef *port;
}Button_st;

/* Functions  -----------------------------------------------------------------*/
_Bool PB_PORT_Init(uint8_t button);
GPIO_PinState PB_PORT_GetState(uint8_t button);
_Bool PB_PORT_DeInit(uint8_t button);

#endif /* API_BUTTON_PORT */
