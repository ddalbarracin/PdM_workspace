/**
 ******************************************************************************
 * @file    API_bmp.c
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   BMP User API
 *
 ******************************************************************************
 **/
/* Includes -----------------------------------------------------------------*/
#include "API_bmp.h"
#include "API_bmp_port.h"

/* Declarate Functions ------------------------------------------------------*/
static void bmpError_Handler(void);

/* Private Functions --------------------------------------------------------*/
/**
 * @func   bmpInit
 * @brief  Initialize BMP Device
 * @param  None
 * @retval _Bool
 */
_Bool bmpInit(void) {

	_Bool stts = false;

	stts = bmpPORT_Init();

	if (stts == false) {

		bmpError_Handler();

	}

	return (stts);
}

/**
 * @func   bmpDeInit
 * @brief  Initialize BMP Device
 * @param  None
 * @retval _Bool
 */
void bmpDeInit(void) {

	bmpPORT_DeInit();

	return;

}

/**
 * @func   bmpGet_Temp
 * @brief  Read Temperature from bmp device
 * @param  None
 * @retval float
 */
float bmpGet_Temp(void) {

	float temp = 0;

	temp = bmpPORT_Get_Temp();

	return (temp);

}

/**
 * @func   bmpGet_Pres
 * @brief  Read Pressure from bmp device
 * @param  None
 * @retval float
 */
float bmpGet_Press(void) {

	float press = 0;

	press = bmpPORT_Get_Press();

	return (press);

}

/**
 * @func   bmpGet_Alt
 * @brief  Read Altitude from bmp device
 * @param  None
 * @retval float
 */
float bmpGet_Alt(void) {

	float alt = 0;

	alt = bmpPORT_Get_Alt();

	return (alt);

}

/**
 * @func   bmpError_Handler
 * @brief  Catch Errors from BMP device
 * @param  None
 * @retval None
 */
static void bmpError_Handler(void) {
	while (1) {

	}

}

