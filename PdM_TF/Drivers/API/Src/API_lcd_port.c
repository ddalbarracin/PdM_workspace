/**
 ******************************************************************************
 * @file    API_lcd_port.c
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   This file make interface between API_lcd and API_i2c.
 *
 ******************************************************************************
 **/
/* Includes ------------------------------------------------------------------ */
#include "API_lcd_port.h"
#include "API_i2c.h"

/* Private Declarate Functions ----------------------------------------------- */
static void lcdPORT_Send_Nibble(uint8_t, uint8_t);
static void lcdPORT_Send_Byte(uint8_t, uint8_t);
static void lcdPORT_Ctrl_Cmnd(uint8_t);
static void lcdPORT_Data_Cmnd(uint8_t);
static void lcdPORT_Line_Pos(uint8_t, uint8_t);
static void lcdPORT_Delay(uint8_t);
static void lcdPORT_Error_Handler(void);
static void lcdPrint_FirstWrite(void);

/*
 * @func   lcdPORT_Init
 * @brief  Initialize LCD
 * @param  None
 * @retval None
 */
_Bool lcdPORT_Init(void){

	_Bool stts = true;

	stts = i2cInit();
	if (stts == true){

		lcdPORT_Delay(LCD_PORT_DELAY50);
		lcdPORT_Ctrl_Cmnd(LCD_PORT_FUNCT_8B);
		lcdPORT_Delay(LCD_PORT_DELAY5);
		lcdPORT_Ctrl_Cmnd(LCD_PORT_FUNCT_8B);
		lcdPORT_Delay(LCD_PORT_DELAY1);
		lcdPORT_Ctrl_Cmnd(LCD_PORT_FUNCT_8B);
		lcdPORT_Delay(LCD_PORT_DELAY10);
		lcdPORT_Ctrl_Cmnd(LCD_PORT_FUNCT_SET);
		lcdPORT_Delay(LCD_PORT_DELAY10);

		/* LCD Initialize */
		lcdPORT_Ctrl_Cmnd(LCD_PORT_FUNCT_4B_2L);
		lcdPORT_Delay(LCD_PORT_DELAY1);
		lcdPORT_Ctrl_Cmnd(LCD_PORT_DISPLAY_OFF);
		lcdPORT_Delay(LCD_PORT_DELAY1);
		lcdPORT_Ctrl_Cmnd(LCD_PORT_CLEAR);
		lcdPORT_Delay(LCD_PORT_DELAY2);
		lcdPORT_Ctrl_Cmnd(LCD_PORT_RETURN_HOME);
		lcdPORT_Delay(LCD_PORT_DELAY1);
		lcdPORT_Ctrl_Cmnd(LCD_PORT_ENTRY_MODE + LCD_PORT_INCREMENT);
		lcdPORT_Delay(LCD_PORT_DELAY1);

		//lcdPORT_Ctrl_Cmnd(CURSOR_SHIFT);
		lcdPORT_Ctrl_Cmnd(LCD_PORT_DISPLAY_ON);
		lcdPORT_Ctrl_Cmnd(LCD_PORT_CLEAR);
		lcdPORT_Delay(LCD_PORT_DELAY5);
		lcdPrint_FirstWrite();

	}

	return(stts);

}

/*
 * @func   lcdPORT_DeInit
 * @brief  DeInitialize LCD
 * @param  None
 * @retval None
 */
void lcdPORT_DeInit(void){

	i2cDeInit();

	return;

}

/*
 * @func   lcdPrint_FirstWrite
 * @brief  First writing to clear lcd character memory
 * @param  None
 * @retval None
 */
static void lcdPrint_FirstWrite(void){

	static const char lcd_blank[] = "             ";

	lcdPORT_Ctrl_Cmnd(LCD_PORT_CLEAR);
	lcdPORT_Ctrl_Cmnd(LCD_PORT_CLEAR);
	lcdPORT_Print((uint8_t *)lcd_blank, LCD_PORT_DDRAM_LH, 3);
	HAL_Delay(1);
	lcdPORT_Print((uint8_t *)lcd_blank, LCD_PORT_DDRAM_LL, 3);
	HAL_Delay(1);
	lcdPORT_Ctrl_Cmnd(LCD_PORT_CLEAR);

	return;

}

/*
 * @func   lcdPORT_Clear
 * @brief  Clear LCD
 * @param  None
 * @retval None
 */
void lcdPORT_Clear(void){

	lcdPORT_Ctrl_Cmnd(LCD_PORT_CLEAR);
	lcdPORT_Delay(LCD_PORT_DELAY5);

	return;
}

/*
 * @func   lcdPORT_Print
 * @brief  Print to LCD
 * @param  uint8_t*, uint8_t, uint8_t
 * @retval None
 */
void lcdPORT_Print(uint8_t *texto, uint8_t line, uint8_t position){

	lcdPORT_Ctrl_Cmnd(LCD_PORT_RETURN_HOME);
	lcdPORT_Line_Pos(line, position);

	while(*texto)lcdPORT_Data_Cmnd(*texto++);

	return;
}

/*
 * @func   lcdPORT_Data_Cmnd
 * @brief  Send data to LCD
 * @param  uint8_t
 * @retval None
 */
static void lcdPORT_Data_Cmnd(uint8_t data){

	lcdPORT_Send_Byte(data, LCD_PORT_DATOS);

	return;

}

/*
 * @func   lcdPORT_Ctrl_Comnd
 * @brief  Send control command to LCD
 * @param  uint8_t
 * @retval None
 */
static void lcdPORT_Ctrl_Cmnd(uint8_t data){

	lcdPORT_Send_Byte(data, LCD_PORT_CONTROL);

	return;

}

/*
 * @func   lcdPORT_Send_Byte
 * @brief  Send byte to LCD
 * @param  uint8_t, uint8_t
 * @retval None
 */
static void lcdPORT_Send_Byte(uint8_t data, uint8_t type){

	uint8_t high = data & LCD_PORT_NIBBLE_MSB;
	uint8_t low = (data << LCD_PORT_NIBBLE_LSB) & LCD_PORT_NIBBLE_MSB;
	lcdPORT_Send_Nibble(high, type);
	lcdPORT_Send_Nibble(low, type);

	return;

}
/*
 * @func   lcdPORT_Send_Nibble
 * @brief  Send Nibble to LCD
 * @param  uint8_t, uint8_t
 * @retval None
 */
static void lcdPORT_Send_Nibble(uint8_t data, uint8_t type){

	_Bool stts;
	uint8_t fdata  = ((data) | (type) | (LCD_PORT_ENABLE) | (LCD_PORT_BACK_LIGHT_ON));
	uint8_t sdata = ((data) | (type) | (LCD_PORT_BACK_LIGHT_ON));

	stts = i2cWrite(fdata);
	if (stts == true){
		lcdPORT_Delay(LCD_PORT_DELAY2);
	}else{
		lcdPORT_Error_Handler();
	}
	stts = i2cWrite(sdata);
	if (stts == true){
		lcdPORT_Delay(LCD_PORT_DELAY2);
	}else{
		lcdPORT_Error_Handler();
	}

	return;

}

/*
 * @func   lcdPORT_Line_Pos
 * @brief  Set a line and a position into LCD
 * @param  uint8_t, uint8_t
 * @retval None
 */
static void lcdPORT_Line_Pos(uint8_t line, uint8_t position){

	uint8_t charPos;

	if ((line == LCD_PORT_DDRAM_LH)||(line == LCD_PORT_DDRAM_LL)){

		if ((position>=0) && (position<= 15)){

			charPos = position+line;
			lcdPORT_Ctrl_Cmnd(charPos);

		}else{

			lcdPORT_Error_Handler();

		}
	}
	else{

		lcdPORT_Error_Handler();

	}

	return;

}

/*
 * @func   lcdPORT_Delay
 * @brief  set a delay
 * @param  uint8_t
 * @retval None
 */
static void lcdPORT_Delay(uint8_t delay){

	HAL_Delay(delay);

	return;
}

/*
 * @func   lcdPORT_Error_Hanlder
 * @brief  catch an error
 * @param  None
 * @retval None
 */
static void lcdPORT_Error_Handler(void){
	while(1){

	}
}
