/** @file main.c
 *  @brief Definition of main function
 *
 *  This is the source file for main function.
 *
 *  @author duattran
 *  @version V1.0
 *
 * ------------------------------ REVISION HISTORY -----------------------------
 * Dec 10, 2022 - Updated file template
 *              - Added GPIO sample - LED blinking
 * -----------------------------------------------------------------------------
 */

/*******************************************************************************
 * 1. Included Files
 ******************************************************************************/
#include "main.h"

/*******************************************************************************
 * 2. Object-like Macros
 ******************************************************************************/
#define SAMPLE_GPIO

/*******************************************************************************
 * 3. Function-like Macros
 ******************************************************************************/

/*******************************************************************************
 * 4. Typedefs: Enumerations, Structures, Unions, Pointers, Others
 ******************************************************************************/
typedef struct
{
	GPIO_TypeDef  *Port;	/* Port */
	uint32_t Pin;			/* Pin */
} GPIO_PortPin;
/*******************************************************************************
 * 5. Global, Static, Constant, Extern Variables and Extern Functions
 ******************************************************************************/
void SystemClock_Config(void);

/*******************************************************************************
 * 6. Function Definitions
 ******************************************************************************/
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  GPIO_PortPin LEDPin = {GPIOA, GPIO_PIN_4};
  HAL_Init(); // Reset of all peripherals, Initializes the Flash interface and the Systick
  SystemClock_Config(); // Configure the system clock

  /**
    * GPIO sample
    */
#ifdef  SAMPLE_GPIO
  __GPIOA_CLK_ENABLE();

  GPIO_InitTypeDef gpioStruct = {0};
  gpioStruct.Pin = GPIO_PIN_4; //
  gpioStruct.Mode = GPIO_MODE_OUTPUT_PP;
  gpioStruct.Pull = GPIO_NOPULL;
  gpioStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  gpioStruct.Alternate = ;

  HAL_GPIO_Init(LEDPin.Port, &gpioStruct);

  while(1)
  {
    HAL_GPIO_TogglePin(LEDPin.Port, LEDPin.Pin);
    HAL_Delay(1000); // Delay 1000ms
  }
#endif /* SAMPLE_GPIO */

  while(1)
  {

  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/** End of File ***************************************************************/
