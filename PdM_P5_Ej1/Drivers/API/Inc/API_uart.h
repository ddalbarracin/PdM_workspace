/**
 ******************************************************************************
 * @file    API_debounce.h
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   PdM - Practical Work 5 - Exercise 1
 * 		 	Header of API_uart.c
 *
 ******************************************************************************
 **/

/* Includes ------------------------------------------------------------------ */
#ifndef API_UART
#define API_UART

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "API_Delay.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"

/* Private define ------------------------------------------------------------*/
/* Definition for USARTx clock resources */
#define USARTx                           USART3
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      USARTx_RX_GPIO_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_8
#define USARTx_TX_GPIO_PORT              GPIOD
#define USARTx_TX_AF                     GPIO_AF7_USART3
#define USARTx_RX_PIN                    GPIO_PIN_9
#define USARTx_RX_GPIO_PORT              USARTx_TX_GPIO_PORT
#define USARTx_RX_AF                     USARTx_TX_AF
#define USARTx_SPEED					 GPIO_SPEED_LOW

/* Definition for USARTx Pins */
#define USARTx_BAUD_RATE				 9600

/* Define for texting by UART ------------------------------------------------*/
#define USART_MSG_NL					"\n\r"
#define USART_MSG_STATUS				"DONE"
#define USART_MSG_WELCOME				"UART Initialize Status: "
#define USART_MSG_PROMT					"CESE-2024-PdM@ddalbarracin:\n\r"
#define USART_MSG_BaudRate 				"\tBaudRate: "
#define USART_MSG_MODE 					"\tMode: "
#define USART_MSG_WORDLENGTH			"\tWordLength: "
#define USART_MSG_STOPBIT 				"\tStopBits: "
#define USART_MSG_PARITY				"\tPartity: "
#define USART_MSG_WORD					8
#define USART_MSG_STOPBITS				1
#define USART_MSG_PARITY_NONE			"None"
#define USART_MSG_MODE_TXRX				"TxRx"


/* Public Functions ----------------------------------------------------------*/

bool_t uartInit();
void uartSendString(uint8_t*);
void uartSendStringSize(uint8_t*, uint16_t);
void uartReceiveStringSize(uint8_t*, uint16_t);


#endif

