/**
 ******************************************************************************
 * @file    API_lcd.h
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   PdM - Final Work
 * 		 	Header of API_lcd.c
 *
 ******************************************************************************
 **/
/* Includes guard ------------------------------------------------------------- */
#ifndef API_LCD
#define API_LCD

/* Includes ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


/* Defines -------------------------------------------------------------------- */
#define LCD_MENU1_LH			"CESE-2024-MENU"
#define LCD_MENU1_LL			"ALTITUD"
#define LCD_MENU2_LH			LCD_MENU1_LL
#define LCD_MENU2_LL			"TEMPERATURA"
#define LCD_MENU3_LH			LCD_MENU2_LL
#define LCD_MENU3_LL			"PRESION"

#define LCD_OPT1				"ALT ="
#define LCD_OPT2				"TEMP ="
#define LCD_OPT3				"PRE ="

#define LCD_TEXT_LENGTH			16
#define LCD_CURSOR_POS			LCD_TEXT_LENGTH
#define LCD_LINE_HIGH			LCD_PORT_DDRAM_LH
#define LCD_LINE_LOW			LCD_PORT_DDRAM_LL
#define LCD_CURSOR_POS_START	0
#define LCD_CURSOR_MSR_ALT		4
#define LCD_CURSOR_MSR_TEMP		5
#define LCD_CURSOR_MSR_PRES		5
#define LCD_CURSOR_UNIT_ALT		13
#define LCD_CURSOR_UNIT_TEMP	12
#define LCD_CURSOR_UNIT_PRES	11



/* Prototypes Functions ------------------------------------------------------ */
_Bool lcdInit(void);
void lcdDeInit(void);
void lcdClear(void);
void lcdFSM_SysInit(void);
void lcdFSM_SysUpdate(void);


#endif /* API_LCD */
