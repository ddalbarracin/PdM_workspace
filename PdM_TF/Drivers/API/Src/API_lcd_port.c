/**
 ******************************************************************************
 * @file    API_lcd_port.c
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   PdM - Final Work
 * 		 	This file make interface between API_lcd and API_i2c.
 *
 ******************************************************************************
 **/

/* Includes ------------------------------------------------------------------ */
#include "API_lcd_port.h"

/* Global Variables ---------------------------------------------------------- */


/* Private Declarate Functions ----------------------------------------------- */

static void lcdPORT_Send_Nibble(uint8_t, uint8_t);
static void lcdPORT_Send_Byte(uint8_t, uint8_t);
static void lcdPORT_Ctrl_Cmnd(uint8_t);
static void lcdPORT_Data_Cmnd(uint8_t);

static void lcdPORT_Line_Pos(uint8_t, uint8_t);
static void lcdPORT_Cursor_Set(_Bool);
static void lcdPORT_Delay(uint8_t);
static void lcdPORT_DataFormat(uint8_t *);
static void lcdPORT_Error_Handler(void);

/*
 * @func   lcdControl_Comnd
 * @brief  Send control commando to LCD
 * @param  uint8_t
 * @retval void
 */
_Bool lcdPORT_Init(void){

	_Bool stts = true;

	stts = i2cInit();
	if (stts == true){
		lcdPORT_Delay(DELAY50);
		lcdPORT_Ctrl_Cmnd(FUNCT_8B);
		lcdPORT_Delay(DELAY5);
		lcdPORT_Ctrl_Cmnd(FUNCT_8B);
		lcdPORT_Delay(DELAY1);
		lcdPORT_Ctrl_Cmnd(FUNCT_8B);
		lcdPORT_Delay(DELAY10);
		lcdPORT_Ctrl_Cmnd(FUNCT_SET);
		lcdPORT_Delay(DELAY10);
		/* LCD Initialize */
		lcdPORT_Ctrl_Cmnd(FUNCT_4B_2L);
		lcdPORT_Delay(DELAY1);
		lcdPORT_Ctrl_Cmnd(DISPLAY_OFF);
		lcdPORT_Delay(DELAY1);
		lcdPORT_Ctrl_Cmnd(CLEAR_LCD);
		lcdPORT_Delay(DELAY2);
		lcdPORT_Ctrl_Cmnd(RETURN_HOME);
		lcdPORT_Delay(DELAY1);
		lcdPORT_Ctrl_Cmnd(ENTRY_MODE + INCREMENT);
		lcdPORT_Delay(DELAY1);
		//lcdPORT_Ctrl_Cmnd(CURSOR_SHIFT);
		lcdPORT_Ctrl_Cmnd(DISPLAY_ON);
		lcdPORT_Ctrl_Cmnd(CLEAR_LCD);
		lcdPORT_Delay(DELAY5);
	}
	return(stts);
}

/*
 * @func   lcdControl_Comnd
 * @brief  Send control commando to LCD
 * @param  uint8_t
 * @retval void
 */
_Bool lcdPORT_DeInit(void){

	_Bool stts = false;

	return(stts);

}

/*
 * @func   lcdPORT_Clear
 * @brief  Send control commando to LCD
 * @param  None
 * @retval None
 */
void lcdPORT_Clear(void){

	lcdPORT_Ctrl_Cmnd(CLEAR_LCD);
	lcdPORT_Delay(DELAY5);
}

/*
 * @func   lcdPORT_Print
 * @brief  Print to LCD
 * @param  uint8_t
 * @retval _Bool
 */
_Bool lcdPORT_Print(uint8_t *texto, uint8_t line, uint8_t position){

	_Bool stts = true;
	lcdPORT_Ctrl_Cmnd(RETURN_HOME);
	lcdPORT_Line_Pos(line, position);


	while(*texto)lcdPORT_Data_Cmnd(*texto++);
	return(stts);
}

/*
 * @func   lcdPORT_Data_Cmnd
 * @brief  Send data commando to LCD
 * @param  uint8_t
 * @retval None
 */
static void lcdPORT_Data_Cmnd(uint8_t data){

	lcdPORT_Send_Byte(data, DATOS);
}

/*
 * @func   lcdPORT_Ctrl_Comnd
 * @brief  Send control commando to LCD
 * @param  uint8_t
 * @retval None
 */
static void lcdPORT_Ctrl_Cmnd(uint8_t data){

	lcdPORT_Send_Byte(data, CONTROL);
}


static void lcdPORT_Send_Byte(uint8_t data, uint8_t type){

	uint8_t high = data & NIBBLE_MSB;
	uint8_t low = (data << NIBBLE_LSB)&NIBBLE_MSB;
	lcdPORT_Send_Nibble(high, type);
	lcdPORT_Send_Nibble(low, type);

}
/*
 * @func   lcdPORT_Send
 * @brief  Send control commando to LCD
 * @param  uint8_t
 * @retval void
 */
static void lcdPORT_Send_Nibble(uint8_t data, uint8_t type){

	_Bool stts;
	uint8_t fdata  = (data | type | ENABLE + BACK_LIGHT_ON);
	uint8_t sdata = (data | type | BACK_LIGHT_ON);

	stts = i2cWrite(fdata);
	if (stts == true){
		lcdPORT_Delay(DELAY2);
	}else{
		lcdPORT_Error_Handler();
	}
	stts = i2cWrite(sdata);
	if (stts == true){
		lcdPORT_Delay(DELAY2);
	}else{
		lcdPORT_Error_Handler();
	}
}

/*
 * @func   lcdPORT_Line_Pos
 * @brief
 * @param  uint8_t
 * @retval void
 */
static void lcdPORT_Line_Pos(uint8_t line, uint8_t position){

	uint8_t charPos;
	if ((line == DDRAM_LH)||(line == DDRAM_LL)){
		if ((position>=0)&& (position<= 15)){
			charPos = position+line;
			lcdPORT_Ctrl_Cmnd(charPos);
		}else{
			lcdPORT_Error_Handler();
		}
	}
	else{
		lcdPORT_Error_Handler();
	}


}

/*
 * @func   lcdPORT_Cursor_Set
 * @brief
 * @param  _Bool
 * @retval void
 */
static void lcdPORT_Cursor_Set(_Bool){

}

/*
 * @func   lcdPORT_Delay
 * @brief
 * @param  uint8_t
 * @retval None
 */
static void lcdPORT_Delay(uint8_t delay){
	HAL_Delay(delay);
}

/*
 * @func   lcdPORT_Error_Hanlder
 * @brief
 * @param  None
 * @retval None
 */
static void lcdPORT_Error_Handler(void){
	while(1){

	}
}
