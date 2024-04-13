/**
 ******************************************************************************
 * @file    API_spi.c
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   File to manage SPI Hardware Module
 *
 ******************************************************************************
 **/
/* Includes ------------------------------------------------------------------ */
#include "API_spi.h"

/* Global Variables -----------------------------------------------------------*/
static SPI_HandleTypeDef spiHandler;
static GPIO_InitTypeDef spiCSHandler;

/* Declarate Functions ----------------------------------------------------------*/
static void spiError_Handler(HAL_StatusTypeDef);
static void spiMspInit(SPI_HandleTypeDef*);
static void spiMspDeInit(void);
static void spiCSGPIOInit(void);
static void spiCSGPIODeInit(void);
static void spiCSLow(void);
static void spiCSHigh(void);
static uint8_t spiReadWrite(uint8_t);

/* Private Functions ----------------------------------------------------------*/
/**
 * @func   spiInit
 * @brief  Initialize SPI Protocol Parameters
 * @param  None
 * @retval _Bool
 */
_Bool spiInit(void){

	HAL_StatusTypeDef spi_stts;
	_Bool stts = false;

	spiHandler.Instance = SPI1_INST;
	spiHandler.Init.Mode = SPI1_MODE;
	spiHandler.Init.BaudRatePrescaler = SPI1_BAUD_RATE_PRESC;
	spiHandler.Init.DataSize = SPI1_DATA_SIZE;
	spiHandler.Init.Direction = SPI1_DIRECTION;
	spiHandler.Init.FirstBit = SPI1_FIRST_BIT;
	spiHandler.Init.CLKPolarity = SPI1_CLK_POL;
	spiHandler.Init.CLKPhase = SPI1_CLK_PHA;
	spiHandler.Init.CRCCalculation = SPI1_CRC_CALC;
	spiHandler.Init.CRCPolynomial = SPI1_CRC_POLY;
	spiHandler.Init.NSS = SPI1_NSS;
	spiHandler.Init.TIMode = SPI1_TIMODE;

	spiMspInit(&spiHandler);

	spi_stts = HAL_SPI_Init(&spiHandler);

	if(spi_stts == HAL_OK){

		stts = true;
		spiCSGPIOInit();

	}
	else{

		spiError_Handler(spi_stts);

	}

	return(stts);
}

/**
 * @func   spiDeInit
 * @brief  DeInitialize SPI Protocol Parameters
 * @param  None
 * @retval None
 */
void spiDeInit(void){

	spiMspDeInit();
	spiCSGPIODeInit();

	return;
}

/**
 * @func   spiREGRead
 * @brief  Regsiter Read from SPI
 * @param  uint8_t
 * @retval uint8_t
 */
uint8_t spiREGRead(uint8_t addr){

	uint8_t spiValue;

	spiCSLow();

	spiReadWrite(addr);
	spiValue = spiReadWrite(0);

	spiCSHigh();

	return(spiValue);

}

/**
 * @func   spiREGWrite
 * @brief  Write a regsiter to SPI
 * @param  uint8_t, uint8_t
 * @retval None
 */
void spiREGWrite(uint8_t addr, uint8_t value){

	uint8_t spiAddr;

	spiAddr = addr & SPI_WRITE_MASK;
	spiCSLow();

	spiReadWrite(spiAddr);
	spiReadWrite(value);

	spiCSHigh();

	return;
}

/**
 * @func   spiBULKRead
 * @brief  Read Multiples Register from SPI
 * @param  uint8_t, uint8_t*, uint8_t
 * @retval None
 */
void spiBULKRead(uint8_t addr, uint8_t *bulk, uint8_t length){

	spiCSLow();

	spiReadWrite(addr);
	while(--length){

		*bulk ++=spiReadWrite(0);

	}

	spiCSHigh();

	return;

}

/**
 * @func   spiReadWrite
 * @brief  Write or Read to/from SPI
 * @param  uint8_t
 * @retval uint8_t
 */
static uint8_t spiReadWrite(uint8_t spiTxDato){

	HAL_StatusTypeDef spi_stts;
	uint8_t spiRxDato;

	spi_stts = HAL_SPI_TransmitReceive(&spiHandler, &spiTxDato, &spiRxDato, ONLY_BYTE, HAL_MAX_DELAY);

	if(spi_stts != HAL_OK){

		spiError_Handler(spi_stts);

	}

	return(spiRxDato);
}

/**
 * @func   spiMspInit
 * @brief  Initialize SPI Low Level Resources Hardware
 * @param  SPI_HandleTypeDef*
 * @retval None
 */
static void spiMspInit(SPI_HandleTypeDef *hspi){

	GPIO_InitTypeDef GPIO_InitStruct;

	/* Enable clock for GPIOA Port */
	SPI1_GPIO_CLK_ENABLE();

		/* Configure GPIO parameters */
	GPIO_InitStruct.Pin = SPI1_SCLK_PIN | SPI1_MOSI_PIN | SPI1_MISO_PIN;
	GPIO_InitStruct.Mode = SPI1_GPIO_MODE;
	GPIO_InitStruct.Speed = SPI1_GPIO_SPEED;
	GPIO_InitStruct.Pull = SPI1_GPIO_NPULL;
	GPIO_InitStruct.Alternate = SPI1_GPIO_AF;

	/* Initialize GPIO Port A */
	HAL_GPIO_Init(SPI1_SPI_PORT, &GPIO_InitStruct);

	/* Enable Peripheral clock */
	SPI1_PERPH_CLK_ENABLE();

	return;

}

/**
 * @func   spiMspDeInit
 * @brief  DeInitialize SPI Low Level Resources Hardware
 * @param  None
 * @retval None
 */
static void spiMspDeInit(void){

	/* Disable clock for GPIO Port B*/
	SPI1_GPIO_CLK_ENABLE();

	/* Disable Peripheral clock */
	SPI1_PERPH_CLK_DISABLE();

	return;

}

/**
 * @func   spiCSGPIOInit
 * @brief  Initialize CS (Chip Select) SPI Hardware I/O
 * @param  None
 * @retval None
 */
static void spiCSGPIOInit(void){

	/* Enable the CS PIN Clock */
	SPI1_CS_GPIO_CLK_ENABLE();

	/* Configure Button pin as input */
	spiCSHandler.Pin = SPI1_CS_PIN;
	spiCSHandler.Mode = SPI1_CS_GPIO_MODE;
	spiCSHandler.Pull = SPI1_CS_GPIO_NPULL;
	spiCSHandler.Speed = SPI1_CS_GPIO_SPEED;
	HAL_GPIO_Init(SPI1_CS_PORT, &spiCSHandler);

	return;

}

/**
 * @func   spiCSGPIODeInit
 * @brief  DeInitialize CS SPI Hardware I/O
 * @param  None
 * @retval None
 */
static void spiCSGPIODeInit(void){

	SPI1_CS_GPIO_CLK_DISABLE();

}

/**
 * @func   spiCSLow
 * @brief  Put to LOW CS PIN
 * @param  None
 * @retval None
 */
static void spiCSLow(void){

	HAL_GPIO_WritePin(SPI1_CS_PORT, spiCSHandler.Pin, GPIO_PIN_RESET);

	return;

}

/**
 * @func   spiCSHigh
 * @brief  Put to High CS PIN
 * @param  None
 * @retval None
 */
static void spiCSHigh(void){

	HAL_GPIO_WritePin(SPI1_CS_PORT, spiCSHandler.Pin, GPIO_PIN_SET);

	return;

}

/**
 * @func   spiError_Handler
 * @brief  Catch an Error
 * @param  HAL_StatusTypeDef
 * @retval None
 */
static void spiError_Handler(HAL_StatusTypeDef){
	while(1){

	}
}
