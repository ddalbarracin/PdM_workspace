/**
 ******************************************************************************
 * @file    API_uart.c
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   PdM - Practical Work 5 - Exercise 1
 * 		 	This file implements uart function over hal
 * @date 	28032024
 ******************************************************************************
 **/

/* Includes ------------------------------------------------------------------ */
#include "API_uart.h"
#include "stm32f4xx_hal_uart.h"
#include "stdlib.h"


/* Private Functions ----------------------------------------------------------*/
void Error_Handler(HAL_StatusTypeDef status);
static void uartInitMessage(void);

/* Global  variables ----------------------------------------------------------*/
static UART_HandleTypeDef uartHandler;

/**
 * @func  uartInit
 * @brief  Initialize UART Module Hardware
 * @param  None
 * @retval bool_t
 */
bool_t uartInit() {

	bool_t stts = false;
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
 * @func   uartSendString
 * @brief
 * @param  delay_t *pstring
 * @retval None
 */
void uartSendString(uint8_t *pstring) {

	HAL_StatusTypeDef uart_stts;
	uint16_t str_size = (uint16_t)strlen((const char*) pstring);

	uart_stts = HAL_UART_Transmit(&uartHandler, pstring, str_size, HAL_MAX_DELAY);

	if (uart_stts != HAL_OK){
		Error_Handler(uart_stts);
	}
}


/**
 * @func  uartSendStringSize
 * @brief
 * @param  delay_t *pstring, uint16_t size
 * @retval None
 */
void uartSendStringSize(uint8_t *pstring, uint16_t size) {
	HAL_StatusTypeDef uart_stts;

	uart_stts = HAL_UART_Transmit(&uartHandler, pstring, size, HAL_MAX_DELAY);
	if (uart_stts != HAL_OK){
			Error_Handler(uart_stts);
	}
}


/**
 * @func  uartReceiveStringSize
 * @brief
 * @param  delay_t *pstring, uint16_t size
 * @retval None
 */
void uartReceiveStringSize(uint8_t *pstring, uint16_t size) {


}


/**
 * @func  Error_Handler
 * @brief
 * @param  delay_t *pstring, uint16_t size
 * @retval None
 */

void Error_Handler(HAL_StatusTypeDef status){
	while(1){

	}
}


static void uartInitMessage(void) {
	char msg[80];
	char itoa_msg[5];

	uint8_t *ptrstring = NULL;
	char *ptrItoa = NULL;
	ptrstring = (uint8_t *) msg;

	memset(msg, '\0', sizeof(msg));
	strcpy(msg, USART_MSG_WELCOME);
	strcat(msg, USART_MSG_STATUS);
	strcat(msg, USART_MSG_NL);
	uartSendString(ptrstring);

	memset(msg, '\0', sizeof(msg));
	memset(itoa_msg, '\0', sizeof(itoa_msg));
	strcpy(msg, USART_MSG_BaudRate);
	ptrItoa = utoa(USARTx_BAUD_RATE, itoa_msg, 10);
	strcat(msg, (const char *)ptrItoa);
	strcat(msg, USART_MSG_NL);
	uartSendString(ptrstring);

	memset(msg, '\0', sizeof(msg));
	strcpy(msg, USART_MSG_MODE);
	strcat(msg, USART_MSG_MODE_TXRX);
	strcat(msg, USART_MSG_NL);
	uartSendString(ptrstring);

	memset(msg, '\0', sizeof(msg));
	memset(itoa_msg, '\0', sizeof(itoa_msg));
	strcpy(msg, USART_MSG_WORDLENGTH);
	ptrItoa = utoa(USART_MSG_WORD, itoa_msg, 10);
	strcat(msg, (const char *)ptrItoa);
	strcat(msg, USART_MSG_NL);
	uartSendString(ptrstring);

	memset(msg, '\0', sizeof(msg));
	memset(itoa_msg, '\0', sizeof(itoa_msg));
	strcpy(msg, USART_MSG_STOPBIT);
	ptrItoa = utoa(USART_MSG_STOPBITS, itoa_msg, 10);
	strcat(msg, (const char *)ptrItoa);
	strcat(msg, USART_MSG_NL);
	uartSendString(ptrstring);

	memset(msg, '\0', sizeof(msg));
	strcpy(msg, USART_MSG_PARITY);
	strcat(msg, USART_MSG_PARITY_NONE);
	strcat(msg, USART_MSG_NL);
	uartSendString(ptrstring);

	return;
}

