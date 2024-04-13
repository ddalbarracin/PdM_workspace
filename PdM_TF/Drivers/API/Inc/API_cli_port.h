/**
 ******************************************************************************
 * @file    API_cli_port.h
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   Header of API_cli_port.c
 *
 ******************************************************************************
 **/
/* Includes guard ------------------------------------------------------------- */
#ifndef API_CLI_PORT
#define API_CLI_PORT

/* Includes ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* Defines ------------------------------------------------------------------- */
#define LSB_NIBBLE_MASK			0x0F
#define MSB_NIBBLE_MASK			0xF0
#define NIBBLE_SHIFT			4
#define MSG_UART_END			"\n\r"
#define MSG_UART_TSTAMP_START	"["
#define MSG_UART_TSTAMP_END		"]:"

/* Prototype Functions -------------------------------------------------------- */
_Bool cliPORT_Init(void);
_Bool cliPORT_DeInit(void);
_Bool cliPORT_Clear(void);
void cliPORT_Print(uint8_t *);

#endif /* API_CLI_PORT */
