/**
 ******************************************************************************
 * @file    API_uart.c
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   This file implements uart functions over hal
 * @date 	13042024
 ******************************************************************************
 **/
/* Includes ------------------------------------------------------------------ */
#include "API_uart.h"
#include "stm32f4xx_hal_uart.h"


/* Private Function Declaration  ----------------------------------------------------------*/
static void Error_Handler(HAL_StatusTypeDef status);
static void uartInitMessage(void);

/* Global  variables ----------------------------------------------------------*/
static UART_HandleTypeDef uartHandler;

/* Private Functions ----------------------------------------------------------*/
/**
 * @func  uartInit
 * @brief  Initialize UART Module Hardware
 * @param  None
 * @retval _Bool
 */
_Bool uartInit(void) {

	_Bool stts = false;
	HAL_StatusTypeDef rtrn;

	uartHandler.Instance = USARTx;

	uartHandler.Init.BaudRate = USARTx_BAUD_RATE;
	uartHandler.Init.Mode = UART_MODE_TX_RX;
	uartHandler.Init.WordLength = UART_WORDLENGTH_9B;
	uartHandler.Init.StopBits = UART_STOPBITS_1;
	uartHandler.Init.Parity = UART_PARITY_ODD;
	uartHandler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uartHandler.Init.OverSampling = UART_OVERSAMPLING_16;

	rtrn = HAL_UART_Init(&uartHandler);

	if (rtrn == HAL_OK) {

		stts = true;
		uartInitMessage();

	} else {

		Error_Handler(rtrn);

	}

	return (stts);

}

/**
 * @func   uartDeInit
 * @brief  DeInitialize UART Module Hardware
 * @param  None
 * @retval _Bool
 */
_Bool uartDeInit(void){

	_Bool stts = false;
	HAL_StatusTypeDef rtrn;

	rtrn = HAL_UART_DeInit(&uartHandler);

	if (rtrn != HAL_OK) {

		Error_Handler(rtrn);

	} else {

		stts = true;

	}

	return (stts);

}

/**
 * @func   uartSendString
 * @brief  Function to transmit a string
 * @param  uint8_t *pstring
 * @retval None
 */
void uartSendString(uint8_t *pstring) {

	HAL_StatusTypeDef uart_stts;

	if (pstring != NULL) {

		uint16_t str_size = (uint16_t) strlen((const char*) pstring);
		uart_stts = HAL_UART_Transmit(&uartHandler, pstring, str_size, HAL_MAX_DELAY);

		if (uart_stts != HAL_OK) {

			Error_Handler(uart_stts);

		}
	}

	return;

}

/**
 * @func   uartSendStringSize
 * @brief  function to transmit a string with a specific size
 * @param  uint8_t *pstring, uint16_t size
 * @retval None
 */
void uartSendStringSize(uint8_t *pstring, uint16_t size) {

	HAL_StatusTypeDef uart_stts;

	if ((pstring != NULL) && (size > 0)) {

		uart_stts = HAL_UART_Transmit(&uartHandler, pstring, size, HAL_MAX_DELAY);

		if (uart_stts != HAL_OK) {

			Error_Handler(uart_stts);

		}
	}

	return;

}

/**
 * @func   Error_Handler
 * @brief  function to catch error uart status
 * @param  delay_t *pstring, uint16_t size
 * @retval None
 */
static void Error_Handler(HAL_StatusTypeDef status) {
	while (1) {

	}
}

/**
 * @func   uartInitMessage
 * @brief  Send an init message
 * @param  None
 * @retval None
 */
static void uartInitMessage(void) {

	char msg[80];

	uint8_t *ptrstring = NULL;
	ptrstring = (uint8_t*) msg;

	memset(msg, MEM_CLR, sizeof(msg));
	strcpy(msg, USART_MSG_SEP);
	uartSendString(ptrstring);

	memset(msg, MEM_CLR, sizeof(msg));
	strcpy(msg, USART_MSG_WELCOME);
	strcat(msg, USART_MSG_NL);
	uartSendString(ptrstring);

	memset(msg, MEM_CLR, sizeof(msg));
	strcpy(msg, USART_MSG_STTS);
	strcat(msg, USART_MSG_STATUS);
	strcat(msg, USART_MSG_NL);
	uartSendString(ptrstring);

	memset(msg, MEM_CLR, sizeof(msg));
	strcpy(msg, USART_MSG_BaudRate);
	strcat(msg, USART_MSG_BAUD_RATE);
	strcat(msg, USART_MSG_NL);
	uartSendString(ptrstring);

	memset(msg, MEM_CLR, sizeof(msg));
	strcpy(msg, USART_MSG_MODE);
	strcat(msg, USART_MSG_MODE_TXRX);
	strcat(msg, USART_MSG_NL);
	uartSendString(ptrstring);

	memset(msg, MEM_CLR, sizeof(msg));
	strcpy(msg, USART_MSG_WORDLENGTH);
	strcat(msg, USART_MSG_WORD);
	strcat(msg, USART_MSG_NL);
	uartSendString(ptrstring);

	memset(msg, MEM_CLR, sizeof(msg));
	strcpy(msg, USART_MSG_STOPBIT);
	strcat(msg, USART_MSG_STOPBITS);
	strcat(msg, USART_MSG_NL);
	uartSendString(ptrstring);

	memset(msg, MEM_CLR, sizeof(msg));
	strcpy(msg, USART_MSG_PARITY);
	strcat(msg, USART_MSG_PARITY_NONE);
	strcat(msg, USART_MSG_NL);
	uartSendString(ptrstring);

	memset(msg, MEM_CLR, sizeof(msg));
	strcpy(msg, USART_MSG_SEP);
	uartSendString(ptrstring);

	uartSendString((uint8_t *) USART_MSG_CESE);
	uartSendString((uint8_t *) USART_MSG_AUTHOR);
	uartSendString((uint8_t *) USART_MSG_GIT);

	memset(msg, MEM_CLR, sizeof(msg));
	strcpy(msg, USART_MSG_SEP);
	uartSendString(ptrstring);

	return;

}

