/**
 ******************************************************************************
 * @file    API_i2c.h
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   Header of API_i2c.c
 *
 ******************************************************************************
 **/
/* Includes guard ------------------------------------------------------------- */
#ifndef API_I2C
#define API_I2C

/* Includes ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"
#include "stm32f4xx_hal_i2c.h"

/* Private define ------------------------------------------------------------*/
/* Definition for I2C resources */
#define I2C1_INST						I2C1
#define I2C1_CLK_FREC					100000
#define I2C1_DUTY_CYCLE					I2C_DUTYCYCLE_2
#define I2C1_OWN_ADD1					0
#define I2C1_ADD_MODE					I2C_ADDRESSINGMODE_7BIT
#define I2C1_DUAL_ADD_MODE				I2C_DUALADDRESS_DISABLE
#define I2C1_OWN_ADD2					0
#define I2C1_GRAL_CALL_MODE				I2C_GENERALCALL_DISABLE
#define I2C1_NOSTRETCH_Mode				I2C_NOSTRETCH_DISABLE

/* Definition for GPIO Parameters */
#define I2C1_SDA_PIN					GPIO_PIN_8
#define I2C1_SCL_PIN					GPIO_PIN_9
#define I2C1_GPIO_PORT					GPIOB
#define I2C1_GPIO_MODE					GPIO_MODE_AF_OD
#define I2C1_GPIO_AF					GPIO_AF4_I2C1
#define I2C1_GPIO_SPEED					GPIO_SPEED_FREQ_LOW
#define I2C1_GPIO_NPULL					GPIO_NOPULL
#define I2C1_GPIO_CLK_ENABLE()  		__HAL_RCC_GPIOB_CLK_ENABLE()
#define I2C1_GPIO_CLK_DISABLE()			__HAL_RCC_GPIOB_CLK_DISABLE()
#define I2C1_PERPH_CLK_ENABLE()			__HAL_RCC_I2C1_CLK_ENABLE()
#define I2C1_PERPH_CLK_DISABLE()		__HAL_RCC_I2C1_CLK_DISABLE()

#define DEV_ADD							(0x27<<1)

/* Functions ------------------------------------------------------------------ */
_Bool i2cInit(void);
void i2cDeInit(void);
_Bool i2cWrite(uint8_t);


#endif /* API_I2C */
