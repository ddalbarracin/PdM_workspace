/**
 ******************************************************************************
 * @file    API_lcd_port.h
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   PdM - Final Work
 * 		 	Header of API_lcd_port.c
 *
 ******************************************************************************
 **/
/* Includes guard ------------------------------------------------------------- */
#ifndef API_LCD_PORT
#define API_LCD_PORT

/* Includes ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "API_i2c.h"


/* LCD Registers ---------------------------------------------------------------
#define INST_REG
#define DATA_REG
#define ADD_COUNT
#define DDRAM
#define CGRAM
*/
/* LCD Commands ----------------------------------------------------------------*/
#define CLEAR_LCD 			(1<<0)
#define RETURN_HOME			(1<<1)
#define ENTRY_MODE			(1<<2)
#define INCREMENT			(1<<1)

#define DISPLAY_OFF			(1<<3)
#define DISPLAY_ON			(3<<2)
#define CURSOR_ON			(7<<1)
#define CURSOR_OFF			(3<<2)
#define CURSOR_BLINK		(0x0F)

#define CURSOR_SHIFT		(5<<2)

#define FUNCT_SET			(1<<5)
#define BUS_4BITS			(0<<4)
#define BUS_8BITS			(1<<4)
#define LINES_2				(1<<3)
#define FUNCT_4B_2L			((1<<5)|(1<<3))
#define FUNCT_8B			((1<<5)|(1<<4))

#define CGRAM_SET			(1<<6)
#define DDRAM_SET			(1<<7)
#define DDRAM_LH			0x80
#define DDRAM_LL			0xC0
#define BUSY_FLAG			(1<<8)
#define WRTIE_DATA			(1<<9)
#define READ_DATA			(2<<9)


#define DELAY50 			50
#define DELAY10 			10
#define DELAY5				5
#define DELAY2  			2
#define DELAY1  			1

#define NIBBLE_MSB 			0xF0
#define NIBBLE_LSB 			4

#define ENABLE 				(1<<2)
#define BACK_LIGHT_ON 		(1<<3)
#define BACK_LIGHT_OFF		(0<<3)

#define DATOS 				1
#define CONTROL 			0


/* Prototype Functions -------------------------------------------------------- */
_Bool lcdPORT_Init(void);
_Bool lcdPORT_DeInit(void);
void lcdPORT_Clear(void);
_Bool lcdPORT_Print(uint8_t *, uint8_t, uint8_t);

#endif /* API_LCD_PORT */
