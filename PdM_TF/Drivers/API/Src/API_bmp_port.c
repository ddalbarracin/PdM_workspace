/**
 ******************************************************************************
 * @file    API_bmp_port.c
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   PdM - Final Work
 * 		 	File to manage bmp_port
 ******************************************************************************
 **/

/* Includes ------------------------------------------------------------------ */
#include "API_bmp_port.h"
#include "API_spi.h"
#include <math.h>

/* Declarate Functions ----------------------------------------------------------*/
static void bmpPORT_Error_Handler(void);
static void bmpPORT_Delay(uint32_t);

static _Bool bmpPORT_BMP_Config(void);
static void bmpPORT_Set_OSPress(void);
static void bmpPORT_Set_OSTemp(void);
static void bmpPORT_Set_PWRMode(void);
static void bmpPORT_Set_IIRCnfg(void);
static void bmpPORT_Set_Reset(void);
static void bmpPORT_Get_CompParam(void);
static void bmpPORT_Set_StandBy(void);
static void bmpPORT_Set_Ref(void);

/* Compensate Alghoritm DataSheet by Copyright (c) 2020 Bosch Sensortec GmbH.*/
static int32_t bmp280_compensate_T_int32(int32_t adc_T);
static uint32_t bmp280_compensate_P_int64(int32_t adc_P);

/* Typedef Definitions --------------------------------------------------------*/
typedef struct{
	uint16_t dig_T1;
	int16_t  dig_T2;
	int16_t  dig_T3;
	uint16_t dig_P1;
	int16_t dig_P2;
	int16_t dig_P3;
	int16_t dig_P4;
	int16_t dig_P5;
	int16_t dig_P6;
	int16_t dig_P7;
	int16_t dig_P8;
	int16_t dig_P9;
}bmpCompP_t;

typedef struct{
	float temp;
	float press;
	float alt;
}bmpMsrmt_t;


/* Global Variables ----------------------------------------------------------*/
static bmpMsrmt_t measr;
static bmpCompP_t compParams;
static float refPress = 0;
static int32_t temp_fine = 0;


/* Private Functions ----------------------------------------------------------*/
/**
 * @func   spiPORT_Init
 * @brief  Initialize SPI PORT
 * @param  None
 * @retval _Bool
 */
_Bool bmpPORT_Init(void){

	_Bool stts = false;

	stts = spiInit();

	if (stts == true){

		stts = bmpPORT_BMP_Config();

	}else{

		bmpPORT_Error_Handler();
	}

	return(stts);
}

/**
 * @func   spiPORT_DeInit
 * @brief  Initialize SPI Protocol Parameters
 * @param  None
 * @retval _Bool
 */
_Bool bmpPORT_DeInit(void){
	_Bool stts = false;

	stts = spiDeInit();

	if (stts == false){

		bmpPORT_Error_Handler();
	}
	return(stts);

}

/**
 * @func   bmpPORT_GetID
 * @brief
 * @param  None
 * @retval uint8_t
 */
uint8_t bmpPORT_GetID(void){

	uint8_t bmpID;

	bmpID = spiREGRead(BMP_REG_ID);

	return(bmpID);
}
/**
 * @func   bmpPORT_Get_Temp
 * @brief
 * @param  None
 * @retval uint32_t *
 */
float bmpPORT_Get_Temp(void){

	int32_t msrdTemp;
	uint8_t tempBuf[BMP_REG_TEMP_QTY];


	spiBULKRead(BMP_REG_TEMP_MSB, tempBuf, BMP_REG_TEMP_QTY);

	msrdTemp = ((tempBuf[0] << 12) | (tempBuf[1] << 4) | (tempBuf[2] >> 4));

	measr.temp = (float)(bmp280_compensate_T_int32(msrdTemp)/100.0);

	return(measr.temp);
}
/**
 * @func   bmpPORT_Get_Pres
 * @brief
 * @param  None
 * @retval uint32_t *
 */
float bmpPORT_Get_Press(void){

	int32_t msrdPress;
	uint8_t pressBuf[BMP_REG_PRESS_QTY];

	spiBULKRead(BMP_REG_PRESS_MSB, pressBuf, BMP_REG_PRESS_QTY);

	msrdPress = ((pressBuf[0] << 12) | (pressBuf[1] << 4) | (pressBuf[2] >> 4));

	measr.press = (float)(bmp280_compensate_P_int64(msrdPress)/256.0);

	return(measr.press);
}

/**
 * @func   bmpPORT_Get_Alt
 * @brief
 * @param  None
 * @retval uint32_t *
 */
float bmpPORT_Get_Alt(void){

	int32_t msrdAlt;
	float msrdPress;

	if (refPress != 0){

		if(measr.press != 0){
			msrdPress = measr.press;
		}else{
			msrdPress = bmpPORT_Get_Press();
		}
		msrdAlt = (float)(1.0 - pow(msrdPress / refPress, 0.1903)) * 4433076.0;
		measr.alt = msrdAlt;
	}

	return(measr.alt);

}

/**
 * @func   bmpPORT_BMP_Config
 * @brief  Initilize BMP Config
 * @param  None
 * @retval None
 */
static _Bool bmpPORT_BMP_Config(void){

	uint8_t bmpID;
	_Bool cnfg_stts = false;

	bmpID = bmpPORT_GetID();

	if (bmpID == BMP_PARAM_ID){

		cnfg_stts = true;

	}else{

		bmpPORT_Set_Reset();
		bmpPORT_Delay(BMP_RST_DELAY);
		bmpID = bmpPORT_GetID();

		if (bmpID == BMP_PARAM_ID){

			cnfg_stts = true;

		}else{

			bmpPORT_Error_Handler();

		}

	}

	if (cnfg_stts == true){

		bmpPORT_Set_OSPress();
		bmpPORT_Set_OSTemp();
		bmpPORT_Set_PWRMode();
		bmpPORT_Set_IIRCnfg();
		bmpPORT_Set_StandBy();
		bmpPORT_Get_CompParam();
		bmpPORT_Set_Ref();

	}

	return(cnfg_stts);

}

/**
 * @func   bmpPORT_Set_OSPress
 * @brief  Set Oversampling mode for Preassure
 * @param  None
 * @retval None
 */
static void bmpPORT_Set_OSPress(void){

	uint8_t msrmnt_reg;

	msrmnt_reg = spiREGRead(BMP_REG_CTRL_MEAS);
	msrmnt_reg &= BMP_PARAM_OSRP_MASK;
	msrmnt_reg |= BMP_PARAM_OSRP;
	spiREGWrite(BMP_REG_CTRL_MEAS, msrmnt_reg);

}

/**
 * @func   bmpPORT_Set_OSTemp
 * @brief  Set Oversampling mode for temperature
 * @param  None
 * @retval None
 */
static void bmpPORT_Set_OSTemp(void){

	uint8_t msrmnt_reg;

	msrmnt_reg = spiREGRead(BMP_REG_CTRL_MEAS);
	msrmnt_reg &= BMP_PARAM_OSRT_MASK;
	msrmnt_reg |= BMP_PARAM_OSRT;
	spiREGWrite(BMP_REG_CTRL_MEAS, msrmnt_reg);

}

/**
 * @func   bmpPORT_Set_PWRMode
 * @brief  Set Power Mode
 * @param  None
 * @retval None
 */
static void bmpPORT_Set_PWRMode(void){

	uint8_t msrmnt_reg;

	msrmnt_reg = spiREGRead(BMP_REG_CTRL_MEAS);
	msrmnt_reg &= BMP_PARAM_PWR_MODE_MASK;
	msrmnt_reg |= BMP_PARAM_PWR_MODE;
	spiREGWrite(BMP_REG_CTRL_MEAS, msrmnt_reg);

}

/**
 * @func   bmpPORT_Set_OSTemp
 * @brief
 * @param  None
 * @retval None
 */
static void bmpPORT_Set_IIRCnfg(void){

	int8_t cnfg_reg;

	cnfg_reg = spiREGRead(BMP_REG_CNFG);
	cnfg_reg &= BMP_PARAM_IIR_MASK;
	cnfg_reg |= BMP_PARAM_IIR;
	spiREGWrite(BMP_REG_CNFG, cnfg_reg);

}

/**
 * @func   bmpPORT_StandBy
 * @brief
 * @param  None
 * @retval None
 */
static void bmpPORT_Set_StandBy(void){

	int8_t cnfg_reg;

	cnfg_reg = spiREGRead(BMP_REG_CNFG);
	cnfg_reg &= BMP_PARAM_STANDBY_MODE_MASK;
	cnfg_reg |= BMP_PARAM_STANDBY_MODE;
	spiREGWrite(BMP_REG_CNFG, cnfg_reg);

}

/**
 * @func   bmpPORT_Reset
 * @brief
 * @param  None
 * @retval None
 */
static void bmpPORT_Set_Reset(void){

	spiREGWrite(BMP_REG_RST, BMP_SW_RST);

}

/**
 * @func   bmpPORT_CompParam
 * @brief
 * @param  None
 * @retval None
 */
static void bmpPORT_Get_CompParam(void){

	uint8_t cmpBuffer[BMP_REG_CAL_LENGTH];

	spiBULKRead(BMP_REG_CAL_INIT, cmpBuffer, BMP_REG_CAL_LENGTH);

	compParams.dig_T1 = (cmpBuffer[1]<<8 | cmpBuffer[0]);
	compParams.dig_T2 = (cmpBuffer[3]<<8 | cmpBuffer[2]);
	compParams.dig_T3 = (cmpBuffer[5]<<8 | cmpBuffer[4]);

	compParams.dig_P1 = (cmpBuffer[7]<<8 | cmpBuffer[6]);
	compParams.dig_P2 = (cmpBuffer[9]<<8 | cmpBuffer[8]);
	compParams.dig_P3 = (cmpBuffer[11]<<8 | cmpBuffer[10]);
	compParams.dig_P4 = (cmpBuffer[13]<<8 | cmpBuffer[12]);
	compParams.dig_P5 = (cmpBuffer[15]<<8 | cmpBuffer[14]);
	compParams.dig_P6 = (cmpBuffer[17]<<8 | cmpBuffer[16]);
	compParams.dig_P7 = (cmpBuffer[19]<<8 | cmpBuffer[18]);
	compParams.dig_P8 = (cmpBuffer[21]<<8 | cmpBuffer[20]);
	compParams.dig_P9 = (cmpBuffer[23]<<8 | cmpBuffer[22]);

}

/**
 * @func   bmpPORT_Set_Ref
 * @brief
 * @param  None
 * @retval None
 */
static void bmpPORT_Set_Ref(void){

	float avrg = 0;
	uint8_t indx;
	for(indx = 0; indx < BMP_SET_PRESS_REF_SMPL; indx ++){

		avrg += bmpPORT_Get_Press();
		bmpPORT_Delay(BMP_SET_PRESS_REF_DELAY);

	}

	refPress = (avrg/BMP_SET_PRESS_REF_SMPL);
}

/**
 * @func   bmp280_compensate_T_int32
 * @brief  Returns temperature in DegC,
 * 		   resolution is 0.01 DegC.
 * 		   Output value of “5123” equals 51.23 DegC.
 * 		   t_fine carries fine temperature as global value
 * @param  int32_t
 * @retval int32_t
 * @author Bosch Sensortec GmbH
 */
static int32_t bmp280_compensate_T_int32(int32_t msrdTemp){

	int32_t var1, var2, Temp;

	var1 = ((((msrdTemp >> 3) - ((int32_t) compParams.dig_T1 << 1)))
			* ((int32_t) compParams.dig_T2)) >> 11;
	var2 = (((((msrdTemp >> 4) - ((int32_t) compParams.dig_T1))
			* ((msrdTemp >> 4) - ((int32_t) compParams.dig_T1))) >> 12)
			* ((int32_t) compParams.dig_T3)) >> 14;

	temp_fine = var1 + var2;

	Temp = (temp_fine * 5 + 128) >> 8;

	return(Temp);

}

/**
 * @func   bmp280_compensate_P_int64
 * @brief  Returns pressure in Pa as unsigned
 * 		   32 bit integer in Q24.8 format
 * 		   (24 integer bits and 8 fractional bits).
 * 		   Output value of “24674867” represents
 * 		   24674867/256 = 96386.2 Pa = 963.862 hPa
 * @param  int32_t
 * @retval uint32_t
 * @author Bosch Sensortec GmbH
 */
static uint32_t bmp280_compensate_P_int64(int32_t msrdPress){

	int32_t var1, var2, Press;

	var1 = ((int64_t)(temp_fine)) - 128000;
	var2 = var1 * var1 * (int64_t)compParams.dig_P6;
	var2 = var2 + ((var1*(int64_t)compParams.dig_P5)<<17);
	var2 = var2 + (((int64_t)compParams.dig_P4)<<35);
	var1 = ((var1 * var1 * (int64_t)compParams.dig_P3)>>8) + ((var1 * (int64_t)compParams.dig_P2)<<12);
	var1 = (((((int64_t)1)<<47)+var1))*((int64_t)compParams.dig_P1)>>33;
	if (var1 == 0)
	{
		return 0; // avoid exception caused by division by zero
	}
	Press = 1048576 - msrdPress;
	Press = (((Press<<31)-var2)*3125)/var1;
	var1 = (((int64_t)compParams.dig_P9) * (Press>>13) * (Press>>13)) >> 25;
	var2 = (((int64_t)compParams.dig_P8) * Press) >> 19;
	Press = ((Press + var1 + var2) >> 8) + (((int64_t)compParams.dig_P7)<<4);

	return ((uint32_t)Press);
}

/**
 * @func   bmpPORT_Delay
 * @brief
 * @param  uint32_t
 * @retval none
 */
static void bmpPORT_Delay(uint32_t delay){
	HAL_Delay(delay);
}

/**
 * @func   bmpPORT_Error_Handler
 * @brief
 * @param  None
 * @retval uint8_t *
 */
static void bmpPORT_Error_Handler(void){

}


