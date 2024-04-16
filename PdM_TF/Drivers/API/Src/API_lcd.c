/**
 ******************************************************************************
 * @file    API_lcd.c
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   PdM - Final Work
 * 		 	File to manage LCD and System FSM
 *
 ******************************************************************************
 **/
/* Includes ---------------------------------------------------------------- */
#include <math.h>
#include <stdlib.h>
#include "API_lcd.h"
#include "API_button.h"
#include "API_cli.h"
#include "API_bmp.h"
#include "API_lcd_port.h"


/* Global Typedef ---------------------------------------------------------- */
typedef enum {
	LCD_STATE_MENU1, LCD_STATE_MENU2, LCD_STATE_MENU3, LCD_STATE_OPT1, LCD_STATE_OPT2, LCD_STATE_OPT3
} lcdFSMState_t;

/* Global Variable ---------------------------------------------------------- */
static lcdFSMState_t LCDState;

static const char uart_start[] = "Data Logger Start";
static const char lcd_title[] = "***CESE--2024***";
static const char lcd_alt[] = "Altitud";
static const char lcd_temp[] = "Temperatura";
static const char lcd_pres[] = "Presion";
static const char lcd_opt1[] = "ALT: ";
static const char lcd_opt1_unit[] = "[m]";
static const char lcd_opt2[] = "TEMP: ";
static const char lcd_opt2_unit[] = { '[', 0xDF, 'C', ']' };
static const char uart_opt2_unit[] = "[॰C]";
static const char lcd_opt3[] = "PRES: ";
static const char lcd_opt3_unit[] = "[hPa]";
static const char uart_Error_Start[] = "Error: ";
static const char uart_Error_Message[] = "LCD Bad Formed Text. ";
static const char uart_Error_End[] = "Please Try Again.";

/* Private Declarate Functions ---------------------------------------------- */

//static void lcdPrint(uint8_t *, uint8_t);
void lcdClear(void);
static uint8_t lcdPrint(uint8_t*, const uint8_t, uint8_t);
static void lcdPrint_Menu1(void);
static void lcdPrint_Menu2(void);
static void lcdPrint_Menu3(void);
static void lcdPrint_Opt1(uint8_t*);
static void lcdPrint_Opt2(uint8_t*);
static void lcdPrint_Opt3(uint8_t*);
static void lcdData2Ascii(float, uint8_t*);
static void lcdError_Handler(void);

/*
 * @func   lcdInit
 * @brief  Initialize LCD
 * @param  None
 * @retval bool_t
 */
_Bool lcdInit(void) {

	_Bool stts = false;

	stts = lcdPORT_Init();
	if (stts != true) {
		lcdError_Handler();
	}

	return (stts);
}

/*
 * @func   lcdDeInit
 * @brief  Initialize LCD
 * @param  None
 * @retval bool_t
 */
void lcdDeInit(void) {

	lcdPORT_DeInit();

	return;
}


/*
 * @func   lcdFSM_SysInit
 * @brief  Initialize FSM System
 * @param  None
 * @retval None
 */
void lcdFSM_SysInit(void){

	/* Initialize BUTTONs */
	uint8_t indx_btn = 0;
	Button_t button[] = { BUTTON_UP, BUTTON_DOWN, BUTTON_ENTER, BUTTON_BACK };
	uint8_t button_size = sizeof(button) / sizeof(Button_t);

	for (indx_btn = 0; indx_btn < button_size; indx_btn++) {

		PB_Init(button[indx_btn]);

	}

	/* Initialize LCD1602 && BMP280 && CLI (UART and RTC) */
	if (lcdInit() && bmpInit() && cliInit()) {

		LCDState = LCD_STATE_MENU1;
		cliPrint((uint8_t*) uart_start, NULL, NULL);
		lcdPrint_Menu1();

	} else {

		lcdDeInit();
		bmpDeInit();
		cliDeInit();
		lcdError_Handler();

	}

	return;
}

/*
 * @func   lcdFSM_SysUpdate
 * @brief  Update FSM System
 * @param  None
 * @retval None
 */
void lcdFSM_SysUpdate(void) {

	Button_t BtnPressed;
	float msr = 0;
	uint8_t pmsr[8];
	BtnPressed = PB_Pressed(PB_STATE_FALL);

	switch (LCDState) {
	case LCD_STATE_MENU1:
		if (BtnPressed == BUTTON_DOWN) {
			LCDState = LCD_STATE_MENU2;
			lcdPrint_Menu2();

		} else {

			if (BtnPressed == BUTTON_ENTER) {
				LCDState = LCD_STATE_OPT1;
				lcdPrint_Opt1(NULL);
				msr = bmpGet_Alt();
				lcdData2Ascii(msr, pmsr);
				lcdPrint_Opt1(pmsr);

			} else {
				LCDState = LCD_STATE_MENU1;

			}
		}
		break;
	case LCD_STATE_MENU2:
		if (BtnPressed == BUTTON_DOWN) {
			LCDState = LCD_STATE_MENU3;
			lcdPrint_Menu3();

		} else {
			if (BtnPressed == BUTTON_ENTER) {
				LCDState = LCD_STATE_OPT2;
				lcdPrint_Opt2(NULL);
				msr = bmpGet_Temp();
				lcdData2Ascii(msr, pmsr);
				lcdPrint_Opt2(pmsr);

			} else {
				if (BtnPressed == BUTTON_UP) {
					LCDState = LCD_STATE_MENU1;
					lcdPrint_Menu1();

				} else {
					LCDState = LCD_STATE_MENU2;

				}
			}
		}
		break;
	case LCD_STATE_MENU3:
		if (BtnPressed == BUTTON_UP) {
			LCDState = LCD_STATE_MENU2;
			lcdPrint_Menu2();

		} else {
			if (BtnPressed == BUTTON_ENTER) {
				LCDState = LCD_STATE_OPT3;
				lcdPrint_Opt3(NULL);
				msr = bmpGet_Press();
				lcdData2Ascii(msr, pmsr);
				lcdPrint_Opt3(pmsr);

			} else {
				LCDState = LCD_STATE_MENU3;

			}
		}
		break;
	case LCD_STATE_OPT1:
		if (BtnPressed == BUTTON_BACK) {
			LCDState = LCD_STATE_MENU1;
			lcdPrint_Menu1();

		} else {
			LCDState = LCD_STATE_OPT1;

		}
		break;
	case LCD_STATE_OPT2:
		if (BtnPressed == BUTTON_BACK) {
			LCDState = LCD_STATE_MENU2;
			lcdPrint_Menu2();

		} else {
			LCDState = LCD_STATE_OPT2;

		}
		break;
	case LCD_STATE_OPT3:
		if (BtnPressed == BUTTON_BACK) {
			LCDState = LCD_STATE_MENU3;
			lcdPrint_Menu3();

		} else {
			LCDState = LCD_STATE_OPT3;

		}
		break;
	default:
		lcdFSM_SysInit();
		break;
	}

}

/*
 * @func   lcdPrint
 * @brief  Print on LCD
 * @param  None
 * @retval None
 */
static uint8_t lcdPrint(uint8_t *text, uint8_t line, uint8_t pos) {

	uint8_t stts = false;
	uint8_t text_size = 0;
	text_size = strlen((const char*) text);

	if ((text_size > 0) && (text_size <= LCD_TEXT_LENGTH)) {

		if ((line == LCD_LINE_HIGH) || (line == LCD_LINE_LOW)) {

			if ((pos >= 0) && (pos < LCD_CURSOR_POS)) {

				lcdPORT_Print(text, line, pos);
				stts = true;

			}
		}
	}

	return (stts);
}

/*
 * @func   lcdClear
 * @brief  Clear LCD
 * @param  None
 * @retval None
 */
void lcdClear(void) {
	lcdPORT_Clear();
}

/*
 * @func   lcdPrint_Menu1
 * @brief  Print Menu1
 * @param  None
 * @retval None
 */
static void lcdPrint_Menu1(void) {

	lcdClear();
	lcdClear();
	if (!(lcdPrint((uint8_t*) lcd_title, LCD_PORT_DDRAM_LH,
			LCD_CURSOR_POS_START))) {

		cliPrint((uint8_t*) uart_Error_Start, (uint8_t*) uart_Error_Message,
				(uint8_t*) uart_Error_End);

	}
	HAL_Delay(1);
	if (!lcdPrint((uint8_t*) lcd_alt, LCD_PORT_DDRAM_LL,
			LCD_CURSOR_POS_START)) {

		cliPrint((uint8_t*) uart_Error_Start, (uint8_t*) uart_Error_Message,
				(uint8_t*) uart_Error_End);

	}
	HAL_Delay(1);

	return;
}

/*
 * @func   lcdPrint_Menu2
 * @brief  Print Menu2
 * @param  None
 * @retval None
 */
static void lcdPrint_Menu2(void) {

	lcdClear();
	lcdClear();
	if (!lcdPrint((uint8_t*) lcd_alt, LCD_PORT_DDRAM_LH,
			LCD_CURSOR_POS_START)) {

		cliPrint((uint8_t*) uart_Error_Start, (uint8_t*) uart_Error_Message,
				(uint8_t*) uart_Error_End);

	}
	HAL_Delay(1);
	if (!lcdPrint((uint8_t*) lcd_temp, LCD_PORT_DDRAM_LL,
			LCD_CURSOR_POS_START)) {

		cliPrint((uint8_t*) uart_Error_Start, (uint8_t*) uart_Error_Message,
				(uint8_t*) uart_Error_End);

	}
	HAL_Delay(1);

	return;
}

/*
 * @func   lcdPrint_Menu3
 * @brief  Print Menu3
 * @param  None
 * @retval None
 */
static void lcdPrint_Menu3(void) {

	lcdClear();
	lcdClear();
	if (!lcdPrint((uint8_t*) lcd_temp, LCD_PORT_DDRAM_LH,
			LCD_CURSOR_POS_START)) {

		cliPrint((uint8_t*) uart_Error_Start, (uint8_t*) uart_Error_Message,
				(uint8_t*) uart_Error_End);

	}
	HAL_Delay(1);
	if (!lcdPrint((uint8_t*) lcd_pres, LCD_PORT_DDRAM_LL,
			LCD_CURSOR_POS_START)) {

		cliPrint((uint8_t*) uart_Error_Start, (uint8_t*) uart_Error_Message,
				(uint8_t*) uart_Error_End);

	}
	HAL_Delay(1);

	return;

}

/*
 * @func   lcdPrint_Opt1
 * @brief  Print Opt1
 * @param  char *
 * @retval None
 */
static void lcdPrint_Opt1(uint8_t *pmsr) {

	lcdClear();
	if (!lcdPrint((uint8_t*) lcd_opt1, LCD_PORT_DDRAM_LH,
			LCD_CURSOR_POS_START)) {

		cliPrint((uint8_t*) uart_Error_Start, (uint8_t*) uart_Error_Message,
				(uint8_t*) uart_Error_End);
	}
	HAL_Delay(1);
	if (pmsr != NULL) {
		if (lcdPrint(pmsr, LCD_PORT_DDRAM_LH, LCD_CURSOR_MSR_ALT)) {

			cliPrint((uint8_t*) lcd_opt1, (uint8_t*) pmsr,
					(uint8_t*) lcd_opt1_unit);

		} else {

			cliPrint((uint8_t*) uart_Error_Start, (uint8_t*) uart_Error_Message,
					(uint8_t*) uart_Error_End);

		}

	}
	HAL_Delay(1);
	if (!lcdPrint((uint8_t*) lcd_opt1_unit, LCD_PORT_DDRAM_LH,
			LCD_CURSOR_UNIT_ALT)) {

		cliPrint((uint8_t*) uart_Error_Start, (uint8_t*) uart_Error_Message,
				(uint8_t*) uart_Error_End);

	}
	HAL_Delay(1);

	return;
}

/*
 * @func   lcdPrint_Opt2
 * @brief  Print Opt2
 * @param  char *
 * @retval None
 */
static void lcdPrint_Opt2(uint8_t *pmsr) {

	lcdClear();
	if (!lcdPrint((uint8_t*) lcd_opt2, LCD_PORT_DDRAM_LH,
			LCD_CURSOR_POS_START)) {

		cliPrint((uint8_t*) uart_Error_Start, (uint8_t*) uart_Error_Message,
				(uint8_t*) uart_Error_End);

	}
	HAL_Delay(1);
	if (pmsr != NULL) {

		if (lcdPrint(pmsr, LCD_PORT_DDRAM_LH, LCD_CURSOR_MSR_TEMP)) {

			cliPrint((uint8_t*) lcd_opt2, (uint8_t*) pmsr,
					(uint8_t*) uart_opt2_unit);

		} else {

			cliPrint((uint8_t*) uart_Error_Start, (uint8_t*) uart_Error_Message,
					(uint8_t*) uart_Error_End);

		}

	}
	HAL_Delay(1);
	if (!lcdPrint((uint8_t*) lcd_opt2_unit, LCD_PORT_DDRAM_LH,
			LCD_CURSOR_UNIT_TEMP)) {

		cliPrint((uint8_t*) uart_Error_Start, (uint8_t*) uart_Error_Message,
				(uint8_t*) uart_Error_End);

	}
	HAL_Delay(1);

	return;

}

/*
 * @func   lcdPrint_Opt3
 * @brief  Print Opt3
 * @param  char *
 * @retval None
 */
static void lcdPrint_Opt3(uint8_t *pmsr) {

	lcdClear();
	if (!lcdPrint((uint8_t*) lcd_opt3, LCD_PORT_DDRAM_LH,
			LCD_CURSOR_POS_START)) {

		cliPrint((uint8_t*) uart_Error_Start, (uint8_t*) uart_Error_Message,
				(uint8_t*) uart_Error_End);

	}
	HAL_Delay(1);
	if (pmsr != NULL) {
		if (lcdPrint(pmsr, LCD_PORT_DDRAM_LH, LCD_CURSOR_MSR_PRES)) {

			cliPrint((uint8_t*) lcd_opt3, (uint8_t*) pmsr,
					(uint8_t*) lcd_opt3_unit);

		} else {

			cliPrint((uint8_t*) uart_Error_Start, (uint8_t*) uart_Error_Message,
					(uint8_t*) uart_Error_End);

		}

	}
	HAL_Delay(1);
	if (!lcdPrint((uint8_t*) lcd_opt3_unit, LCD_PORT_DDRAM_LH,
			LCD_CURSOR_UNIT_PRES)) {

		cliPrint((uint8_t*) uart_Error_Start, (uint8_t*) uart_Error_Message,
				(uint8_t*) uart_Error_End);

	}
	HAL_Delay(1);

	return;

}

/*
 * @func   lcdData2Ascii
 * @brief  Convert float to ascii
 * @param  float, uint8_t*
 * @retval None
 */
static void lcdData2Ascii(float msr, uint8_t *svalue) {

	char str[8];
	float read = msr;
	volatile uint8_t flag = 0;

	char digit4[5];
	char digit3[4];
	char digit2[3];
	char fracc[3];

	/* float convert to integer */

	/* get integer part of float */
	int intPart = (int) read;
	/* get decimal part of flat */
	float fracPart = read - intPart;
	/* truncate to two decimal digits */
	int fracInt = trunc(fracPart * 100);

	/* convert integer to ascci */

	if (intPart > 100) {
		/* it's a pressure value */
		if (intPart > 1000) {
			/* pressure has 4 digitis */
			memset(digit4, '\0', sizeof(digit4));
			itoa(intPart, digit4, 10);
			flag = 4;

		} else {
			/* pressure has 3 digits */
			memset(digit3, '\0', sizeof(digit3));
			itoa(intPart, digit3, 10);
			flag = 3;

		}

	} else {
		/* it's an altitude or temperature value */
		memset(digit2, '\0', sizeof(digit2));
		itoa(intPart, digit2, 10);
		flag = 2;
	}
	memset(svalue, '\0', sizeof(str));
	for (uint8_t indx = 0; indx < flag; indx++) {

		if (flag == 2) {
			svalue[indx] = digit2[indx];
		}
		if (flag == 3) {
			svalue[indx] = digit3[indx];
		}
		if (flag == 4) {
			svalue[indx] = digit4[indx];
		}
	}
	svalue[flag] = '.';
	memset(fracc, '\0', sizeof(fracc));
	itoa(fracInt, fracc, 10);
	svalue[flag + 1] = fracc[0];
	svalue[flag + 2] = fracc[1];

	return;

}

/*
 * @func   lcdError_Handler
 * @brief  Print Opt3
 * @param  char *
 * @retval None
 */
static void lcdError_Handler(void) {
	while (1) {

	}
}
