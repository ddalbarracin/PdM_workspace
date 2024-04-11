/**
 ******************************************************************************
 * @file    API_spi.h
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   PdM - Final Work
 * 		 	Header of API_spi.c
 *
 ******************************************************************************
 **/
/* Includes guard ------------------------------------------------------------- */
#ifndef API_SPI
#define API_SPI

/* Includes ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stm32f4xx.h>



/* Private define ------------------------------------------------------------*/
/* Definition for SPI resources */
#define SPI1_INST					SPI1
#define SPI1_MODE					SPI_MODE_MASTER
#define SPI1_BAUD_RATE_PRESC		SPI_BAUDRATEPRESCALER_64
#define SPI1_DATA_SIZE				SPI_DATASIZE_8BIT
#define SPI1_DIRECTION				SPI_DIRECTION_2LINES
#define SPI1_FIRST_BIT				SPI_FIRSTBIT_MSB
#define SPI1_CLK_POL				SPI_POLARITY_LOW
#define SPI1_CLK_PHA				SPI_PHASE_1EDGE
#define SPI1_CRC_CALC				SPI_CRCCALCULATION_DISABLE
#define SPI1_CRC_POLY				7
#define SPI1_NSS					SPI_NSS_SOFT
#define SPI1_TIMODE					SPI_TIMODE_DISABLE

/* Definition for GPIO Parameters */
#define SPI1_SCLK_PIN					GPIO_PIN_3
#define SPI1_MOSI_PIN					GPIO_PIN_5
#define SPI1_MISO_PIN					GPIO_PIN_4
#define SPI1_CS_PIN						GPIO_PIN_4

#define SPI1_CS_PORT					GPIOA
#define SPI1_SPI_PORT					GPIOB

#define SPI1_GPIO_MODE					GPIO_MODE_AF_OD
#define SPI1_GPIO_AF					GPIO_AF5_SPI1
#define SPI1_GPIO_SPEED					GPIO_SPEED_FREQ_HIGH
#define SPI1_GPIO_NPULL					GPIO_PULLUP

#define SPI1_CS_GPIO_MODE				GPIO_MODE_OUTPUT_OD
#define SPI1_CS_GPIO_SPEED				GPIO_SPEED_FREQ_HIGH
#define SPI1_CS_GPIO_NPULL				GPIO_NOPULL

/* Definition for Clock */
#define SPI1_GPIO_CLK_ENABLE()  		__HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI1_GPIO_CLK_DISABLE()			__HAL_RCC_GPIOB_CLK_DISABLE()

#define SPI1_CS_GPIO_CLK_ENABLE()  		__HAL_RCC_GPIOA_CLK_ENABLE()
#define SPI1_CS_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOA_CLK_DISABLE()


#define SPI1_PERPH_CLK_ENABLE()			__HAL_RCC_SPI1_CLK_ENABLE()
#define SPI1_PERPH_CLK_DISABLE()		__HAL_RCC_SPI1_CLK_DISABLE()

#define ONLY_BYTE						1
#define SPI_WRITE_MASK					0x7F

/* Functions ------------------------------------------------------------------ */
_Bool spiInit(void);
_Bool spiDeInit(void);
uint8_t spiREGRead(uint8_t);
void spiREGWrite(uint8_t, uint8_t);
void spiBULKRead(uint8_t, uint8_t*, uint8_t);



#endif /* API_SPI */
