/**
 ******************************************************************************
 * @file    API_rtc.c
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief  This file manage Real Time Clock
 *
 ******************************************************************************
 **/
/* Includes -----------------------------------------------------------------*/
#include "API_rtc.h"
#include "stm32f4xx_hal_rtc.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_pwr.h"

/* Global Variables ---------------------------------------------------------*/
static RTC_HandleTypeDef rtcHandler;
volatile time_t rtc_Current_Time;
volatile date_t rtc_Current_Date;

/* Private Functions --------------------------------------------------------*/
static void rtcError_Handler(HAL_StatusTypeDef);
static void rtcMspInit(RTC_HandleTypeDef*);
static void rtcMspDeInit(void);
static _Bool rtcSetTime(void);
static _Bool rtcSetDate(void);

/* Private Functions --------------------------------------------------------*/
/**
 * @func   rtcInit
 * @brief  Initialize RTC Hardware Module
 * @param  None
 * @retval bool_t
 */
_Bool rtcInit(void) {

	HAL_StatusTypeDef rtc_stts;
	_Bool stts = false;

	rtcHandler.Instance = RTC_HW;
	rtcHandler.Init.HourFormat = RTC_HOUR_FRMT;
	rtcHandler.Init.OutPut = RTC_OUT_DISABLE;
	rtcHandler.Init.OutPutPolarity = RTC_OUT_POL;
	rtcHandler.Init.OutPutType = RTC_OUT_OD;
	rtcHandler.Init.SynchPrediv = RTC_SYNC_PREDEV;
	rtcHandler.Init.AsynchPrediv = RTC_ASYNC_PREDEV;

	rtcMspInit(&rtcHandler);
	rtc_stts = HAL_RTC_Init(&rtcHandler);

	if (rtc_stts == HAL_OK) {

		if ((rtcSetDate()) && (rtcSetTime())) {

			stts = true;

		}

	} else {

		rtcError_Handler(rtc_stts);

	}

	return (stts);
}

/**
 * @func   rtcDeInit
 * @brief  DeInitialize RTC Hardware Module
 * @param  None
 * @retval _Bool
 */
_Bool rtcDeInit(void) {

	HAL_StatusTypeDef rtc_stts;
	_Bool stts = false;

	rtcMspDeInit();
	rtc_stts = HAL_RTC_DeInit(&rtcHandler);

	if (rtc_stts == HAL_OK) {

		stts = true;

	} else {

		rtcError_Handler(rtc_stts);

	}

	return (stts);
}

/**
 * @func   rtcMspInit
 * @brief  Initialize RTC Source Clocks
 * @param  RTC_HandleTypeDef *
 * @retval None
 */
static void rtcMspInit(RTC_HandleTypeDef *hrtc) {

	HAL_StatusTypeDef rtc_stts;
	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI
			| RCC_OSCILLATORTYPE_LSE;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	RCC_OscInitStruct.LSEState = RCC_LSE_ON;
	RCC_OscInitStruct.LSIState = RCC_LSI_OFF;

	rtc_stts = HAL_RCC_OscConfig(&RCC_OscInitStruct);

	if (rtc_stts != HAL_OK) {

		rtcError_Handler(rtc_stts);

	}

	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
	PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
	rtc_stts = HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

	if (rtc_stts != HAL_OK) {

		rtcError_Handler(rtc_stts);

	}

	/* Enable RTC Clock */
	HAL_PWR_EnableBkUpAccess();
	__HAL_RCC_RTC_CONFIG(RCC_RTCCLKSOURCE_LSE);
	__HAL_RCC_RTC_ENABLE();

	return;
}

/**
 * @func   rtcMspDeInit
 * @brief  DeInitialize RTC Hardware Module
 * @param  RTC_HandleTypeDef *
 * @retval None
 */
static void rtcMspDeInit(void) {

	/* Disable RTC Clock */
	HAL_PWR_DisableBkUpAccess();
	__HAL_RCC_RTC_DISABLE();

	return;

}

/**
 * @func   rtcGetTime
 * @brief  get RTC Time
 * @param  None
 * @retval time_t
 */
time_t rtcGetTime(void) {

	HAL_StatusTypeDef rtc_stts;
	RTC_DateTypeDef rtcDate;
	RTC_TimeTypeDef rtcTime;

	rtc_stts = HAL_RTC_GetTime(&rtcHandler, &rtcTime, RTC_FORMAT_BCD);
	rtc_stts = HAL_RTC_GetDate(&rtcHandler, &rtcDate, RTC_FORMAT_BCD);

	if (rtc_stts == HAL_OK) {

		rtc_Current_Time.hour = rtcTime.Hours;
		rtc_Current_Time.minute = rtcTime.Minutes;
		rtc_Current_Time.second = rtcTime.Seconds;

	} else {

		rtcError_Handler(rtc_stts);

	}

	return (rtc_Current_Time);

}

/**
 * @func   rtcSetInit
 * @brief  Initialize RTC Config Time
 * @param  None
 * @retval bool_t
 */
_Bool rtcSetTime(void) {

	HAL_StatusTypeDef rtc_stts;
	RTC_TimeTypeDef rtcTime;
	_Bool stts = false;

	rtcTime.Hours = RTC_SET_TIME_HOUR;
	rtcTime.Minutes = RTC_SET_TIME_MINUTE;
	rtcTime.Seconds = RTC_SET_TIME_SECOND;
	rtcTime.TimeFormat = RTC_SET_TIME_FRMT;
	rtcTime.DayLightSaving = RTC_SET_TIME_DAY_SAV;
	rtcTime.StoreOperation = RTC_SET_TIME_STROP;

	rtc_stts = HAL_RTC_SetTime(&rtcHandler, &rtcTime, RTC_FORMAT_BCD);

	if (rtc_stts == HAL_OK) {

		stts = true;

	} else {

		rtcError_Handler(rtc_stts);
	}

	return (stts);

}

/**
 * @func   rtcGetDate
 * @brief  Get RTC Time
 * @param  None
 * @retval date_t
 */
date_t rtcGetDate(void) {

	HAL_StatusTypeDef rtc_stts;
	RTC_DateTypeDef rtcDate;
	RTC_TimeTypeDef rtcTime;

	rtc_stts = HAL_RTC_GetTime(&rtcHandler, &rtcTime, RTC_FORMAT_BCD);
	rtc_stts = HAL_RTC_GetDate(&rtcHandler, &rtcDate, RTC_FORMAT_BCD);

	if (rtc_stts == HAL_OK) {

		rtc_Current_Date.date = rtcDate.Date;
		rtc_Current_Date.month = rtcDate.Month;
		rtc_Current_Date.year = rtcDate.Year;

	} else {

		rtcError_Handler(rtc_stts);

	}

	return (rtc_Current_Date);

}

/**
 * @func   rtcSetDate
 * @brief  Set RTC Time
 * @param  None
 * @retval _Bool
 */
_Bool rtcSetDate(void) {

	HAL_StatusTypeDef rtc_stts;
	RTC_DateTypeDef rtcDate;
	_Bool stts = false;

	rtcDate.WeekDay = RTC_SET_DATE_WDAY;
	rtcDate.Month = RTC_SET_DATE_MONTH;
	rtcDate.Date = RTC_SET_DATE_DATE;
	rtcDate.Year = RTC_SET_DATE_YEAR;

	rtc_stts = HAL_RTC_SetDate(&rtcHandler, &rtcDate, RTC_FORMAT_BCD);

	if (rtc_stts == HAL_OK) {

		stts = true;

	} else {

		rtcError_Handler(rtc_stts);

	}

	return (stts);

}

/**
 * @func   rtcError_Handler
 * @brief  Catch RTC Errors
 * @param  HAL_StatusTypeDef*
 * @retval None
 */
static void rtcError_Handler(HAL_StatusTypeDef stts) {
	while (1) {

	}
}
