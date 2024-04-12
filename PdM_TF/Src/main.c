/**
 ******************************************************************************
 * @file    main.c
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   CESE - FIUBA 2024 - PdM - PCSE - Final Work
 *
 * @date
 ******************************************************************************
 **/

/* Includes ------------------------------------------------------------------ */
#include "main.h"
#include "API_lcd.h"
#include "API_bmp.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* UART handler declaration */
UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);
/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void) {
	/* STM32F4xx HAL library initialization:
	 - Configure the Flash prefetch
	 - Systick timer is configured by default as source of time base, but user
	 can eventually implement his proper time base source (a general purpose
	 timer for example or other time source), keeping in mind that Time base
	 duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
	 handled in milliseconds basis.
	 - Set NVIC Group Priority to 4
	 - Low Level Initialization
	 */
	HAL_Init();

	/* Configure the system clock to 180 MHz */
	SystemClock_Config();

	/* Variables */
	Led_TypeDef leds[] = { LED_GREEN, LED_BLUE, LED_RED };
	uint8_t size_leds = (uint8_t) (sizeof(leds) / sizeof(Led_TypeDef));
	delay_t tick_led[size_leds];
	uint8_t indx_led = 0;
	uint8_t indx_btn = 0;
	tick_t duty_led[SEQUENCY] = { PERIOD_100, PERIOD_200, PERIOD_300,
	PERIOD_400, PERIOD_500, PERIOD_0 };
	_Bool uart_stts = false;
	_Bool rtc_stts = false;
	_Bool lcd_stts = false;
	_Bool bmp_stts = false;
	tick_t *ptrduty = duty_led;

	/* Initialize BUTTONs */
	Button_t button[] = { BUTTON_UP, BUTTON_DOWN, BUTTON_ENTER, BUTTON_BACK};
	//Button_t button[] = { BUTTON_UP };

	uint8_t button_size = sizeof(button) / sizeof(Button_t);

	for (indx_btn = 0; indx_btn < button_size; indx_btn++) {
		PB_Init(button[indx_btn]);
	}

	/* Initialize UART Hardware */
	if (uartInit()) {

		uart_stts = true;

	} else {
		Error_Handler();
	}
	/* Initialize RTC */
	if (rtcInit()){

		rtc_stts = true;

	}
	/* Initialize Leds */
	for (indx_led = 0; indx_led < size_leds; indx_led++) {
		BSP_LED_Init(leds[indx_led]);
		delayInit(&tick_led[indx_led], *ptrduty);
	}

	/* Initialize LCD1602 */
	if(lcdInit()){
		lcd_stts = true;
	}
	if(bmpInit()){
		bmp_stts = true;
	}
	/* Initilize Button Debounce FSM */
	debounceFSM_init();

	/* Initilize System FSM */
	lcdFSM_SysInit();

	/* Infinite loop */
	while (1) {
		for (indx_led = 0; indx_led < size_leds; indx_led++) {
			if (delayRead(&tick_led[indx_led])) {
				BSP_LED_Toggle(leds[indx_led]);
			}
		}
		/* Update Button Debounce FSM */
		debounceFSM_update();

		/* Update System  FSM */
		lcdFSM_SysUpdate();


		if (PB_Pressed(PB_STATE_FALL)==BUTTON_UP) {
			ptrduty++;
			if ((*ptrduty) == 0) {
				ptrduty = duty_led;
			}
			for (indx_led = 0; indx_led < size_leds; indx_led++) {
				delayInit(&tick_led[indx_led], *ptrduty);
			}

			if (uart_stts&&rtc_stts) {
				uartSendStringSize((uint8_t*) USART_MSG_FALL, strlen((const char*) USART_MSG_FALL));
			}
			if (lcd_stts){
				static const char lcd_uart[] = "BENJA CRACK\n\r";
				uartSendStringSize((uint8_t*) lcd_uart, strlen((const char *) lcd_uart));
			}
			if(bmp_stts){
				static const char spi_txt1[] = "SPI Initialized\n\r";
				uartSendStringSize((uint8_t*) spi_txt1, strlen((const char *) spi_txt1));
			}
		}

		/*if (PB_Pressed(PB_STATE_RISE)==BUTTON_DOWN) {
			if (uart_stts&&rtc_stts) {
				if (lcd_stts){
					uartSendStringSize((uint8_t*) USART_MSG_RISE, strlen((const char*) USART_MSG_RISE));
				}
			}
		}*/
	}
	return (0);
}



/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 180000000
 *            HCLK(Hz)                       = 180000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 8000000
 *            PLL_M                          = 8
 *            PLL_N                          = 360
 *            PLL_P                          = 2
 *            PLL_Q                          = 7
 *            PLL_R                          = 2
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale1 mode
 *            Flash Latency(WS)              = 5
 * @param  None
 * @retval None
 */
static void SystemClock_Config(void) {
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();

	/* The voltage scaling allows optimizing the power consumption when the device is
	 clocked below the maximum system frequency, to update the voltage scaling value
	 regarding system frequency refer to product datasheet.  */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 360;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}

	if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}
}
/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void) {
	/* Turn LED2 on */
	BSP_LED_On(LED2);
	while (1) {
	}
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/* Private functions ---------------------------------------------------------*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
