/**
 ******************************************************************************
 * @file    API_i2c.c
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   PdM - Final Work
 * 		 	File to manage i2c hardware module
 *
 ******************************************************************************
 **/

/* Includes ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "API_i2c.h"


/* Global Variables -----------------------------------------------------------*/
static I2C_HandleTypeDef i2cHandler;

/* Declarate Functions ----------------------------------------------------------*/
static void i2cMspInit(I2C_HandleTypeDef *);
static void i2cError_Handler(HAL_StatusTypeDef);
static void i2cMspDeInit(void);

/* Private Functions ----------------------------------------------------------*/
/**
 * @func   i2cInit
 * @brief  Initialize I2C Protocol Parameters
 * @param  None
 * @retval bool_t
 */
_Bool i2cInit(void){

	HAL_StatusTypeDef i2c_stts;
	_Bool stts = false;

	i2cHandler.Instance = I2C1_INST;
	i2cHandler.Init.ClockSpeed = I2C1_CLK_FREC;
	i2cHandler.Init.DutyCycle = I2C1_DUTY_CYCLE;
	i2cHandler.Init.OwnAddress1 = I2C1_OWN_ADD1;
	i2cHandler.Init.AddressingMode = I2C1_ADD_MODE;
	i2cHandler.Init.DualAddressMode = I2C1_DUAL_ADD_MODE;
	i2cHandler.Init.OwnAddress2 = I2C1_OWN_ADD2;
	i2cHandler.Init.GeneralCallMode = I2C1_GRAL_CALL_MODE;
	i2cHandler.Init.NoStretchMode = I2C1_NOSTRETCH_Mode;

	i2cMspInit(&i2cHandler);

	i2c_stts = HAL_I2C_Init(&i2cHandler);
	if(i2c_stts == HAL_OK){
		stts = true;
	}
	else{
		i2cError_Handler(i2c_stts);
	}

	return (stts);
}

/**
 * @func   i2cDeInit
 * @brief  DeInitialize I2C Protocol Parameters
 * @param  None
 * @retval None
 */
bool_t i2cDeInit(void){
	_Bool stts = false;

	i2cMspDeInit();

	return(stts);
}

/**
 * @func   i2cMspInit
 * @brief  Initialize I2C Hardware Module
 * @param  None
 * @retval bool_t
 */
static void i2cMspInit(I2C_HandleTypeDef *hi2c){

	GPIO_InitTypeDef GPIO_InitStruct;

	/* Enable clock for GPIOF Port */
	I2C1_GPIO_CLK_ENABLE();

	/* Configure GPIO parameters */
	GPIO_InitStruct.Pin = I2C1_SCL_PIN | I2C1_SDA_PIN;
	GPIO_InitStruct.Mode = I2C1_GPIO_MODE;
	GPIO_InitStruct.Speed = I2C1_GPIO_SPEED;
	GPIO_InitStruct.Pull = I2C1_GPIO_NPULL;
	GPIO_InitStruct.Alternate = I2C1_GPIO_AF;

	/* Initialize GPIO Port F */
	HAL_GPIO_Init(I2C1_GPIO_PORT, &GPIO_InitStruct);

	/* Enable RCC clock */
	I2C1_PERPH_CLK_ENABLE();

}

/**
 * @func   i2cMspDeInit
 * @brief  DeInitialize I2C Hardware Module
 * @param  None
 * @retval None
 */
static void i2cMspDeInit(void){

	/* Disable clock for GPIO Port F */
	I2C1_GPIO_CLK_DISABLE();

	/* Disable Peripheral clock */
	I2C1_PERPH_CLK_DISABLE();
}

/**
 * @func   i2cMspDeInit
 * @brief  DeInitialize I2C Hardware Module
 * @param  None
 * @retval None
 */
bool_t i2cWrite(uint8_t data){

	HAL_StatusTypeDef i2c_stts;
	_Bool stts = false;

	i2c_stts = HAL_I2C_Master_Transmit(&i2cHandler, DEV_ADD, &data, sizeof(data), HAL_MAX_DELAY);
	if (i2c_stts == HAL_OK){
		stts = true;
	}
	else{
		i2cError_Handler(i2c_stts);
	}
	return(stts);
}
/**
 * @func   i2cError_Handler
 * @brief  Error control for I2C Software Module
 * @param  None
 * @retval bool_t
 */
static void i2cError_Handler(HAL_StatusTypeDef eHandler){
	while(1){

	}
}

