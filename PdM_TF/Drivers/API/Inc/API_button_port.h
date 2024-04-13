/**
 ******************************************************************************
 * @file    API_button_port.h
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   Header of API_button_port.c
 *
 ******************************************************************************
 */
/* includes  guard-----------------------------------------------------------------*/
#ifndef API_BUTTON_PORT
#define API_BUTTON_PORT

/* includes  -----------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

/* Defines  -----------------------------------------------------------------*/
#define PB_PORT_MODE 				GPIO_MODE_INPUT
#define PB_PORT_PULL 				GPIO_NOPULL
#define PB_PORT_SPEED 				GPIO_SPEED_FAST

#define PB_PORT_UP_PIN				GPIO_PIN_12
#define PB_PORT_DOWN_PIN			GPIO_PIN_13
#define PB_PORT_ENTER_PIN			GPIO_PIN_1
#define PB_PORT_BACK_PIN			GPIO_PIN_0

#define PB_PORT_UP_PORT				GPIOF
#define PB_PORT_DOWN_PORT			GPIOF
#define PB_PORT_ENTER_PORT			GPIOG
#define PB_PORT_BACK_PORT			GPIOG

#define PB_PORT_QTY						4

/* Typedef  -----------------------------------------------------------------*/
typedef struct {
	uint8_t index;
	uint32_t pin;
	uint32_t mode;
	uint32_t pull;
	uint32_t speed;
	GPIO_TypeDef *port;
}Button_st;

typedef enum{
	BUTTON_UP = 0,
	BUTTON_DOWN = 1,
	BUTTON_ENTER = 2,
	BUTTON_BACK = 3,
	BUTTON_NONE = 4,
}Button_t;

/* Functions  -----------------------------------------------------------------*/
_Bool PB_PORT_Init(uint8_t button);
_Bool PB_PORT_DeInit(uint8_t button);
GPIO_PinState PB_PORT_GetState(uint8_t button);


#endif /* API_BUTTON_PORT */
