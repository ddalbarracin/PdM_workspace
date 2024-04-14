/**
 ******************************************************************************
 * @file    API_bmp_port.h
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   Header of API_bmp_port.c
 *
 ******************************************************************************
 **/
/* Includes guard -----------------------------------------------------------*/
#ifndef API_BMP_PORT
#define API_BMP_PORT

/* Includes -----------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/* Private defines ----------------------------------------------------------*/
/* Definition for BMP resources */
/* Registers ----------------------------------------------------------------*/
#define BMP_REG_ID					0xD0	// ID Register
#define BMP_REG_RST					0xE0	// Reset Register
#define BMP_REG_STTS				0xF3	// Status Register
#define BMP_REG_CTRL_MEAS			0xF4	// Measurement Control Register
#define BMP_REG_CNFG				0xF5	// Configuration Register

#define BMP_REG_PRESS_MSB			0XF7	// Read MSB Pressure Register
#define BMP_REG_PRESS_LSB			0XF8	// Read LSB Pressure Register
#define BMP_REG_PRESS_XLSB			0XF9	// Read XLSSB Pressure Register
#define BMP_REG_PRESS_QTY			3

#define BMP_REG_TEMP_MSB			0XFA	// Read MSB Temperature Register
#define BMP_REG_TEMP_LSB			0XFB	// Read LSB Temperature Register
#define BMP_REG_TEMP_XLSB			0XFC	// Read XLSB Temperature Register
#define BMP_REG_TEMP_QTY			3

#define BMP_REG_CAL_INIT			0x88	// Calibration Register Init
#define BMP_REG_CAL_LENGTH			24		// Calibration Register Length

/* Commands -----------------------------------------------------------------*/
#define BMP_SW_RST					0xB6	// Software Reset

/* Parameters ---------------------------------------------------------------*/
#define BMP_PARAM_ID				0x58	// BMP Device ID

/* DataSheet Table 7:
 * Recommended filter settings
 * based on use cases */
#define BMP_PARAM_OSRP				0x0E	// Oversampling Pres x16
#define BMP_PARAM_OSRT				0x02	// Oversampling Temp x2
#define BMP_PARAM_PWR_MODE			0x03	// Power Mode Normal

#define BMP_PARAM_OSRP_MASK			0xE3	// Oversampling Pres x16 Mask
#define BMP_PARAM_OSRT_MASK			0x1F	// Oversampling Temp x16 Mask
#define BMP_PARAM_PWR_MODE_MASK		0xFC	// ower Mode Normal Mask

#define BMP_PARAM_IIR				0x04	// IIR Coeficient 16
#define BMP_PARAM_IIR_MASK			0xE3	// IIR Coeficient Mask
#define BMP_PARAM_STANDBY_MODE		0x00	// StandBy Mode 500 [us]
#define BMP_PARAM_STANDBY_MODE_MASK	0x1F	// StandBy Mode Mask

#define BMP_RST_DELAY				500		// 500 [ms]
#define BMP_SET_PRESS_REF_SMPL		100		// 100 samples of pressure averaged by IIR
#define BMP_SET_PRESS_REF_DELAY		16		// 500 [us] per sample * 16 samples of IIR * 2 of guard = 16 [ms]

/* Prototype Declaration Functions ------------------------------------------*/
_Bool bmpPORT_Init(void);
void bmpPORT_DeInit(void);
uint8_t bmpPORT_GetID(void);
float bmpPORT_Get_Temp(void);
float bmpPORT_Get_Press(void);
float bmpPORT_Get_Alt(void);

#endif /* API_BMP_PORT */
