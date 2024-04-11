/**
 ******************************************************************************
 * @file    API/Inc/API_gpio.h
 * @author  Daniel David Albarracin
 * @brief   Header for API_gpio.c module
 ******************************************************************************
 */
/* include guard -------------------------------------------------------------*/
#ifndef API_GPIO
#define API_GPIO

/* includes  -----------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
#include "API_button_port.h"
#include "stm32f4xx_nucleo_144.h"


/* Defines  -----------------------------------------------------------------*/
#define PButton_GPIO_PORT_CLK_ENABLE(PB_PORT) 		if (PB_PORT == GPIOC) \
													{ \
														__HAL_RCC_GPIOC_CLK_ENABLE(); \
													} \
													if (PB_PORT == GPIOD) \
													{ \
														__HAL_RCC_GPIOD_CLK_ENABLE(); \
													} \
													if (PB_PORT == GPIOG) \
													{ \
														__HAL_RCC_GPIOG_CLK_ENABLE(); \
													} \
													if (PB_PORT == GPIOF) \
													{ \
														__HAL_RCC_GPIOF_CLK_ENABLE(); \
													}

#define PButton_GPIO_PORT_CLK_DISABLE(PB_PORT) 		if (PB_PORT == GPIOC) \
													{ \
														__HAL_RCC_GPIOC_CLK_DISABLE(); \
													} \
													if (PB_PORT == GPIOD) \
													{ \
														__HAL_RCC_GPIOD_CLK_DISABLE(); \
													} \
													if (PB_PORT == GPIOG) \
													{ \
														__HAL_RCC_GPIOG_CLK_DISABLE(); \
													} \
													if (PB_PORT == GPIOF) \
													{ \
														__HAL_RCC_GPIOF_CLK_DISABLE(); \
													}



/* Typedef  -----------------------------------------------------------------*/
typedef enum
{
  PB_MODE_GPIO = 0,
  PB_MODE_EXTI = 1
}ButtonM_t;


/* Prototype Functions ------------------------------------------------------------ */
_Bool GPIO_Init(Button_st *ptr_button);
_Bool GPIO_DeInit(Button_st *ptr_button);
GPIO_PinState GPIO_GetState(Button_st *ptr_button);

#endif /* API_GPIO */
