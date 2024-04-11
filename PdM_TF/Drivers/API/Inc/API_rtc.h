/**
 ******************************************************************************
 * @file    API_rtc.h
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   PdM - Final Work
 * 		 	Header of API_rtc.c
 *
 ******************************************************************************
 **/
/* Includes guard ------------------------------------------------------------- */
#ifndef API_RTC
#define API_RTC

/* Includes ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "API_Delay.h"
#include "stm32f429xx.h"
#include "stm32f4xx_hal_rtc.h"
#include "stm32f4xx_hal_pwr.h"


/* Private defines ------------------------------------------------------------*/
/* Definition for RTC clock resources */
#define RTC_HW							RTC
#define RTC_HOUR_FRMT					RTC_HOURFORMAT_24
#define RTC_OUT_DISABLE					RTC_OUTPUT_DISABLE
#define RTC_OUT_POL						RTC_OUTPUT_POLARITY_HIGH
#define RTC_OUT_OD						RTC_OUTPUT_TYPE_OPENDRAIN
#define RTC_ASYNC_PREDEV				127
#define RTC_SYNC_PREDEV					255
/* RTC_TimeTypeDef */
#define RTC_PC_APB1_CLK_ENABLE			__HAL_RCC_PWR_CLK_ENABLE()
#define RTC_CLK_SRC						RCC_RTCCLKSOURCE_LSE
#define RTC_CLK_SRC_CNFG				__HAL_RCC_RTC_CONFIG(RTC_CLK_SRC)
#define RTC_ENABLE						__HAL_RCC_RTC_ENABLE()
#define RTC_DISABLE						__HAL_RCC_RTC_DISABLE()

#define RTC_TIME_FORMAT					RTC_FORMAT_BCD
#define RTC_DATE_FORMAT					RTC_FORMAT_BCD

#define RTC_SET_TIME_HOUR					0x16
#define RTC_SET_TIME_MINUTE					0x45
#define RTC_SET_TIME_SECOND					0x00
#define RTC_SET_TIME_FRMT					RTC_HOURFORMAT12_PM
#define RTC_SET_TIME_DAY_SAV				RTC_DAYLIGHTSAVING_NONE
#define RTC_SET_TIME_STROP					RTC_STOREOPERATION_RESET

#define RTC_SET_DATE_WDAY					RTC_WEEKDAY_THURSDAY
#define RTC_SET_DATE_MONTH					RTC_MONTH_JANUARY
#define RTC_SET_DATE_DATE					0x19
#define RTC_SET_DATE_YEAR					0x12

/* TypeDef ------------------------------------------------------------------ */
typedef struct{
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
}time_t;

typedef struct {
	uint8_t date;
	uint8_t month;
	uint8_t year;
}date_t;

/* Functions ------------------------------------------------------------------ */
_Bool rtcInit(void);
_Bool rtcDeInit(void);
time_t rtcGetTime(void);
date_t rtcGetDate(void);


#endif /* API_RTC */
