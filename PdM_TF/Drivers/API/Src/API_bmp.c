/**
 ******************************************************************************
 * @file    API_bmp_port.h
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   PdM - Final Work
 * 		 	Header of API_bmp_port.c
 *
 ******************************************************************************
 **/
/* Includes ------------------------------------------------------------------ */
#include "API_bmp.h"
#include "API_bmp_port.h"

/* Global Variables -----------------------------------------------------------*/


/* Declarate Functions ----------------------------------------------------------*/
static void bmpError_Handler(void);


/* Private Functions ----------------------------------------------------------*/
/**
 * @func   bmpInit
 * @brief  Initialize bmp Device
 * @param  None
 * @retval bool_t
 */
_Bool bmpInit(void){

	_Bool stts = false;

	stts = bmpPORT_Init();
	if (stts == false){
		bmpError_Handler();
	}

	return(stts);
}

/**
 * @func   bmpDeInit
 * @brief  Initialize bmp Device
 * @param  None
 * @retval bool_t
 */
_Bool bmpDeInit(void){

	_Bool stts = false;

	stts = bmpPORT_DeInit();
	if (stts == false){
		bmpError_Handler();
	}

	return(stts);
}

/**
 * @func   bmpGet_ID
 * @brief  Get Device ID
 * @param  None
 * @retval bool_t
 */
uint8_t bmpGet_ID(void){

	uint8_t bmpID;
	bmpID = bmpPORT_GetID();
	return(bmpID);
}
/**
 * @func   bmpGet_Temp
 * @brief  Read Temperature from bmp device
 * @param  None
 * @retval float
 */
float bmpGet_Temp(void){

	float temp = 0;

	temp = bmpPORT_Get_Temp();

	return(temp);

}

/**
 * @func   bmpGet_Pres
 * @brief  Read Pressure from bmp device
 * @param  None
 * @retval float
 */
float bmpGet_Press(void){

	float press = 0;

	press = bmpPORT_Get_Press();

	return(press);

}

/**
 * @func   bmpGet_Alt
 * @brief  Read Altitude from bmp device
 * @param  None
 * @retval float
 */
float bmpGet_Alt(void){

	float alt = 0;

	alt = bmpPORT_Get_Alt();

	return(alt);

}

/**
 * @func   bmpError_Handler
 * @brief  Catch Errors from bmp device
 * @param  None
 * @retval uint32_t *
 */
static void bmpError_Handler(void){
	while(1){

	}

}

