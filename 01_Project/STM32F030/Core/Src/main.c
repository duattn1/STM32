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
 * Dec 14, 2022 - Updated comments for GPIO sample
 *              - Added GPIO external interrupt sample
 * -----------------------------------------------------------------------------
 */

/*******************************************************************************
 * 1. Included Files
 ******************************************************************************/
#include "main.h"

/*******************************************************************************
 * 2. Object-like Macros
 ******************************************************************************/
//#define SAMPLE1_GPIO
#define SAMPLE2_GPIO_EXTI

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
GPIO_PortPin LED = {GPIOA, GPIO_PIN_4};
GPIO_PortPin Button1 = {GPIOA, GPIO_PIN_1};
GPIO_PortPin Button2 = {GPIOA, GPIO_PIN_2};

void SystemClock_Config(void);

/*******************************************************************************
 * 6. Function Definitions
 ******************************************************************************/
/**
  * @brief  EXTI0_1 interrupt handler
  */
void EXTI0_1_IRQHandler(void)
{
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1); // PA1: GPIO_PIN_1
	HAL_GPIO_WritePin(LED.Port, LED.Pin, GPIO_PIN_SET); // Turn LED on
}

/**
  * @brief  EXTI1_2 interrupt handler
  */
void EXTI2_3_IRQHandler(void)
{
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_2); // PA2: GPIO_PIN_2
	HAL_GPIO_WritePin(LED.Port, LED.Pin, GPIO_PIN_RESET); // Turn LED off
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  HAL_Init(); // Reset of all peripherals, Initializes the Flash interface and the Systick
  SystemClock_Config(); // Configure the system clock

#ifdef  SAMPLE1_GPIO
	/*
	 * 1. Configure GPIO pin(s): LED - PA4
	 * - Step 1: Enable clock for GPIO port in RCC (Reset and Clock Control) register
	 * - Step 2: Configure GPIO pin(s)
	 * + Mode in GPIOx_MODER
	 * + For output/AF mode: output type in GPIOx_OTYPER and output speed GPIOx_OSPEEDR
	 * + Pull-up/pull-down activation in GPIOx_PUPDR
	 * + For AF mode: alternation function in GPIOx_AFRL or GPIOx_AFRH
	 */
	__GPIOA_CLK_ENABLE(); // Enable clock for GPIOA

	/*
	 * Configure the LED pin (PA4) as output,
	 * and the rest settings as default (push-pull and low speed output, no pull-up/pull-down activated)
	 */
	GPIO_InitTypeDef gpioStruct = {0};
	gpioStruct.Pin = LED.Pin;
	gpioStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioStruct.Pull = GPIO_NOPULL;
	gpioStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED.Port, &gpioStruct);

  while(1)
  {
    HAL_GPIO_TogglePin(LED.Port, LED.Pin);
    HAL_Delay(1000); // Delay 1000 ticks
  }
#endif /* SAMPLE1_GPIO */

#ifdef  SAMPLE2_GPIO_EXTI
	/*
	 * 1. Configure GPIO pin(s): LED - PA4, Button1 - PA1, Button2 - PA2
	 * - Step 1: Enable clock for GPIO port in RCC (Reset and Clock Control) register
	 * - Step 2: Configure GPIO pin(s)
	 * + Mode in GPIOx_MODER
	 * + For output/AF mode: output type in GPIOx_OTYPER and output speed GPIOx_OSPEEDR
	 * + Pull-up/pull-down activation in GPIOx_PUPDR
	 * + For AF mode: alternation function in GPIOx_AFRL or GPIOx_AFRH
	 */
	__GPIOA_CLK_ENABLE(); // Enable clock for GPIOA

	/*
	 * Configure the LED pin (PA4) as output,
	 * and the rest settings as default (push-pull and low speed output, no pull-up/pull-down activated)
	 */
	GPIO_InitTypeDef gpioStruct = {0};
	gpioStruct.Pin = LED.Pin;
	gpioStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioStruct.Pull = GPIO_NOPULL;
	gpioStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED.Port, &gpioStruct);

	/*
	 * Configure the PA1 and PA2 as pull-up input.
	 */
	gpioStruct.Pin = Button1.Pin | Button2.Pin;
	gpioStruct.Mode = GPIO_MODE_INPUT;
	gpioStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(Button1.Port, &gpioStruct); // Button1 and Button2 both locate on GPIOA

	/*
	 * 2. Configure EXTI
	 * - Step 1: Enable clock for SYSCFG
	 * - Step 1.2: Select 1 GPIO line of EXTIx[3:0] bits in SYSCFG_EXTICRx register
	 * - Step 2: For interrupt, configure interrupt mask in EXTI_IMR register
	 * - Step 3: Select interrupt trigger type (falling trigger OR/AND rising trigger) in EXTI_RTSR and EXTI_FTSR
	 *
	 * [Notes]:
	 * - CMSIS libraries also support configure EXTI by calling HAL_GPIO_Init() function
	 *  with Mode of GPIO_MODE_IT_FALLING/GPIO_MODE_IT_RISING/GPIO_MODE_IT_RISING_FALLING.
	 *  Below lines of code just clarify that process in HAL_GPIO_Init().
	 */
	__HAL_RCC_SYSCFG_CLK_ENABLE(); // Enable SYSCFG clock
	/* PA1 and PA2 are default selections on EXTI1[3:0] and EXTI2[3:0] of SYSCFG_EXTICR1 register */
	EXTI->IMR |= (0b1 << 1) | (0b1 << 2);
	EXTI->FTSR |= (0b1 << 1) | (0b1 << 2);


	/*
	 * 3. Configure priority and enable interrupt line
	 * - Step 1: Set priority for interrupt line
	 * - Step 2: Enable interrupt line
	 *
	 * [Notes]:
	 * - Some GPIO external interrupts are grouped into one line. In STM32F030F4P6, there are
	 * three line group for GPIO pins:
	 * + EXTI Line[1:0] for pin 0 to pin 1
	 * + EXTI Line[3:2] for pin 2 to pin 3
	 * + EXTI Line[15:4] for pin 4 to pin 15
	 * In each group, interrupt occurs when at least one pin member got the external signal
	 */
	  HAL_NVIC_SetPriority(EXTI0_1_IRQn, 3, 0);
	  HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

	  HAL_NVIC_SetPriority(EXTI2_3_IRQn, 5, 0);
	  HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);
	while(1)
	{

	}
#endif /* SAMPLE2_GPIO_EXTI */
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
