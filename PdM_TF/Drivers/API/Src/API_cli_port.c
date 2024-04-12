/**
 ******************************************************************************
 * @file    API_cli_port.c
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   PdM - Final Work
 * 		 	This file controls cli port interface
 *
 ******************************************************************************
 **/

/* Includes ------------------------------------------------------------------ */
#include "API_cli_port.h"

/* Private Prototype Functions -------------------------------------------------------- */
static void cliPORT_Error_Handler(void);
static void cliPORT_Get_Date(uint8_t []);
static void cliPORT_Get_Time(uint8_t []);
//static void cliPORT_Data_Format(uint8_t *);


/* Functions -------------------------------------------------------- */
/*
 * @func   cliPORT_Init
 * @brief
 * @param  None
 * @retval _Bool
 */
_Bool cliPORT_Init(void){

	_Bool stts = false;

	return(stts);
}

/*
 * @func   cliPORT_DeInit
 * @brief
 * @param  None
 * @retval _Bool
 */
_Bool cliPORT_DeInit(void){

	_Bool stts = false;

	return(stts);

}

/*
 * @func   cliPORT_Clear
 * @brief
 * @param  None
 * @retval _Bool
 */
_Bool cliPORT_Clear(void){

	_Bool stts = false;

	return(stts);
}

/*
 * @func   cliPORT_Print
 * @brief
 * @param  None
 * @retval _Bool
 */
void cliPORT_Print(uint8_t *text){

	uint8_t timestamp[80];
	uint8_t hour[8];
	uint8_t date[8];

	memset(timestamp, '\0', sizeof(timestamp));
	memset(hour, '\0', sizeof(hour));
	memset(date, '\0', sizeof(date));

	cliPORT_Get_Date(date);
	cliPORT_Get_Time(hour);

	strcpy((char *) timestamp, MSG_UART_TSTAMP_START);
	for (int indx = 0; indx < sizeof(date); indx ++){
		timestamp[indx +1] = date[indx];
	}
	strcat((char *) timestamp, " ");
	for (int indx = 0; indx < sizeof(hour); indx ++){
			timestamp[indx + 10] = hour[indx];
	}

	strcat((char *) timestamp, MSG_UART_TSTAMP_END);
	strcat((char *) timestamp, (char *) text);
	strcat((char *) timestamp, (char *) MSG_UART_END);

	uartSendStringSize((uint8_t*) timestamp, strlen((const char*) timestamp));

	return;

}

/*
 * @func   cliPORT_Get_Date
 * @brief
 * @param  None
 * @retval None
 */
static void cliPORT_Get_Date(uint8_t *date){

	volatile date_t rtc_Date = {0};
	volatile uint8_t dia[2], mes[2], anio[2];

	rtc_Date = rtcGetDate();

	if ((rtc_Date.date > 0)&&(rtc_Date.date <= 31)){

		dia[1] = ((rtc_Date.date & MSB_NIBBLE_MASK) >> NIBBLE_SHIFT);
		dia[0] = (rtc_Date.date & LSB_NIBBLE_MASK);
		mes[1] = ((rtc_Date.month & MSB_NIBBLE_MASK) >> NIBBLE_SHIFT);
		mes[0] = (rtc_Date.month & LSB_NIBBLE_MASK);
		anio[1] = ((rtc_Date.year & MSB_NIBBLE_MASK) >> NIBBLE_SHIFT);
		anio[0] = (rtc_Date.year & LSB_NIBBLE_MASK);

		date[0] = '0' + dia[1];
		date[1] = '0' + dia[0];
		date[2] = '/';
		date[3] = '0' + mes[1];
		date[4] = '0' + mes[0];
		date[5] = '/';
		date[6] = '0' + anio[1];
		date[7] = '0' + anio[0];
	}else{
		cliPORT_Error_Handler();
	}
	return;
}

/*
 * @func   cliPORT_Get_Time
 * @brief
 * @param  None
 * @retval None
 */
static void cliPORT_Get_Time(uint8_t *hour){

	time_t rtc_Time = { .hour = 0, .minute = 0, .second = 0};
	uint8_t hora[2], min[2], seg[2];

	memset(hora, '\0', sizeof(hora));
	memset(min, '\0', sizeof(hora));
	memset(seg, '\0', sizeof(hora));

	rtc_Time = rtcGetTime();

	if ((rtc_Time.hour >= 0) && (rtc_Time.hour <= 24)){

		hora[1] = ((rtc_Time.hour & MSB_NIBBLE_MASK) >> NIBBLE_SHIFT);
		hora[0] = (rtc_Time.hour & LSB_NIBBLE_MASK);
		min[1] = ((rtc_Time.minute & MSB_NIBBLE_MASK) >> NIBBLE_SHIFT);
		min[0] = (rtc_Time.minute & LSB_NIBBLE_MASK);
		seg[1] = ((rtc_Time.second & MSB_NIBBLE_MASK) >> NIBBLE_SHIFT);
		seg[0] = (rtc_Time.second & LSB_NIBBLE_MASK);

		hour[0] = '0' + hora[1];
		hour[1] = '0' + hora[0];
		hour[2] = ':';
		hour[3] = '0' + min[1];
		hour[4] = '0' + min[0];
		hour[5] = ':';
		hour[6] = '0' + seg[1];
		hour[7] = '0' + seg[0];
	}else{
		cliPORT_Error_Handler();
	}
	return;
}

/*
 * @func   cliError_Handler
 * @brief
 * @param  None
 * @retval None
 */
static void cliPORT_Error_Handler(void){
	while(1){

	}

}
