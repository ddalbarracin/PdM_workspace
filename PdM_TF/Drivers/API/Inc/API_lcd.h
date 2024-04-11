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
#include <string.h>
#include "API_Delay.h"
#include "API_lcd_port.h"

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



/* Prototypes Functions ------------------------------------------------------ */
_Bool lcdInit(void);
_Bool lcdDeInit(void);
void lcdClear(void);
void lcdFSM_SysInit(void);
void lcdFSM_SysUpdate(void);
void lcdPrint(uint8_t *, const uint8_t, uint8_t);

#endif /* API_LCD */
