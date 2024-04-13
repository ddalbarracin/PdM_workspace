/**
 ******************************************************************************
 * @file    API_lcd_port.h
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief 	Header of API_lcd_port.c
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


/* LCD Registers ---------------------------------------------------------------
#define INST_REG
#define DATA_REG
#define ADD_COUNT
#define DDRAM
#define CGRAM
*/
/* LCD Commands ----------------------------------------------------------------*/
#define LCD_PORT_CLEAR	 				(1<<0)
#define LCD_PORT_RETURN_HOME			(1<<1)
#define LCD_PORT_ENTRY_MODE				(1<<2)
#define LCD_PORT_INCREMENT				(1<<1)

#define LCD_PORT_DISPLAY_OFF			(1<<3)
#define LCD_PORT_DISPLAY_ON				(3<<2)
#define LCD_PORT_CURSOR_ON				(7<<1)
#define LCD_PORT_CURSOR_OFF				(3<<2)
#define LCD_PORT_CURSOR_BLINK			(0x0F)

#define LCD_PORT_CURSOR_SHIFT			(5<<2)

#define LCD_PORT_FUNCT_SET				(1<<5)
#define LCD_PORT_BUS_4BITS				(0<<4)
#define LCD_PORT_BUS_8BITS				(1<<4)
#define LCD_PORT_LINES_2				(1<<3)
#define LCD_PORT_FUNCT_4B_2L			((1<<5)|(1<<3))
#define LCD_PORT_FUNCT_8B				((1<<5)|(1<<4))

#define LCD_PORT_CGRAM_SET				(1<<6)
#define LCD_PORT_DDRAM_SET				(1<<7)
#define LCD_PORT_DDRAM_LH				0x80
#define LCD_PORT_DDRAM_LL				0xC0
#define LCD_PORT_BUSY_FLAG				(1<<8)
#define LCD_PORT_WRTIE_DATA				(1<<9)
#define LCD_PORT_READ_DATA				(2<<9)


#define LCD_PORT_DELAY50 				50
#define LCD_PORT_DELAY10 				10
#define LCD_PORT_DELAY5					5
#define LCD_PORT_DELAY2  				2
#define LCD_PORT_DELAY1  				1

#define LCD_PORT_NIBBLE_MSB 			0xF0
#define LCD_PORT_NIBBLE_LSB 			4

#define LCD_PORT_ENABLE 				(1<<2)
#define LCD_PORT_BACK_LIGHT_ON 			(1<<3)
#define LCD_PORT_BACK_LIGHT_OFF			(0<<3)

#define LCD_PORT_DATOS 					1
#define LCD_PORT_CONTROL 				0


/* Prototype Functions -------------------------------------------------------- */
_Bool lcdPORT_Init(void);
void lcdPORT_DeInit(void);
void lcdPORT_Clear(void);
void lcdPORT_Print(uint8_t *, uint8_t, uint8_t);

#endif /* API_LCD_PORT */
