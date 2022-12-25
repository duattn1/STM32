/** @file main.c
 *  @brief Definition of main function
 *
 *  This is the source file for main function.
 *
 *  @author duattran
 *  @version V1.0
 *
 * ------------------------------ REVISION HISTORY -----------------------------
 * Dec 25, 2022 - Initialized the project which uses libopencm3
 *              - Added main.c file
 * -----------------------------------------------------------------------------
 */

/*******************************************************************************
 * 1. Included Files
 ******************************************************************************/
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

/*******************************************************************************
 * 2. Object-like Macros
 ******************************************************************************/

/*******************************************************************************
 * 3. Function-like Macros
 ******************************************************************************/

/*******************************************************************************
 * 4. Typedefs: Enumerations, Structures, Unions, Pointers, Others
 ******************************************************************************/
typedef unsigned long uint32_t;

/*******************************************************************************
 * 5. Global, Static, Constant, Extern Variables and Extern Functions
 ******************************************************************************/
int main(void);

/* STM32F030F4P6 vector table */
uint32_t *vector_table[] __attribute__((section(".isr_vector"))) = {
    (uint32_t *)(0x20000000 + 4*1024), // initial stack pointer
	(uint32_t *)main, 			// main as Reset_Handler
	(uint32_t *)0,				// NMI interrupt ISR
	(uint32_t *)0,				// HardFault interrupt ISR
	(uint32_t *)0,				// <Reserved>
	(uint32_t *)0,				// <Reserved>
	(uint32_t *)0,				// <Reserved>
	(uint32_t *)0,				// <Reserved>
	(uint32_t *)0,				// <Reserved>
	(uint32_t *)0,				// <Reserved>
	(uint32_t *)0,				// <Reserved>
	(uint32_t *)0,				// SVCall interrupt ISR
	(uint32_t *)0,				// <Reserved>
	(uint32_t *)0,				// <Reserved>
	(uint32_t *)0,				// PenSV interrupt ISR
	(uint32_t *)0,				// SysTick interrupt ISR
	(uint32_t *)0,				// WWDG interrupt ISR
	(uint32_t *)0,				// <Reserved>
	(uint32_t *)0,				// RTC interrupt ISR
	(uint32_t *)0,				// FLASH interrupt ISR
	(uint32_t *)0, 				// RCC interrupt ISR
	(uint32_t *)0,				// EXTI0_1 interrupt ISR
	(uint32_t *)0,				// EXTI2_3 interrupt ISR
	(uint32_t *)0,				// EXTI4_15 interrupt ISR
	(uint32_t *)0,				// <Reserved>
	(uint32_t *)0,				// DMA_CH1 interrupt ISR
	(uint32_t *)0,				// DMA_CH2_3 interrupt ISR
	(uint32_t *)0,				// DMA_CH4_5 interrupt ISR
	(uint32_t *)0,				// ADC interrupt ISR
	(uint32_t *)0,				// TIM1_BRK_UP_TRG_COM interrupt ISR
	(uint32_t *)0,				// TIM1_CC interrupt ISR
	(uint32_t *)0,				// <Reserved>
	(uint32_t *)0,				// TIM3 interrupt ISR
	(uint32_t *)0,				// <Reserved> / TIM6 interrupt ISR
	(uint32_t *)0,				// <Reserved>
	(uint32_t *)0,				// TIM14 interrupt ISR
	(uint32_t *)0,				// TIM15 interrupt ISR
	(uint32_t *)0,				// TIM16 interrupt ISR
	(uint32_t *)0,				// TIM17 interrupt ISR
	(uint32_t *)0,				// I2C1 interrupt ISR
	(uint32_t *)0,				// I2C2 interrupt ISR
	(uint32_t *)0,				// SPI1 interrupt ISR
	(uint32_t *)0,				// SPI2 interrupt ISR
	(uint32_t *)0,				// USART1 interrupt ISR
	(uint32_t *)0,				// USART2 interrupt ISR
	(uint32_t *)0,				// USART3_4_5_6 interrupt ISR
	(uint32_t *)0,				// Reserved
	(uint32_t *)0 				// USB interrupt ISR
};

/*******************************************************************************
 * 6. Function Definitions
 ******************************************************************************/
/**
  * @brief  The application entry point.
  */
int main(void){
	int i;

	/* Enable GPIOC clock. */
	rcc_periph_clock_enable(RCC_GPIOA);

	/* Set GPIO4 (in GPIO port A) to 'output push-pull'. */
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO4);

	for (;;) {
		gpio_clear(GPIOA, GPIO4); /* LED on */
		for (i = 0; i < 500000; i++) /* Wait a bit. */
		__asm__("nop");

		gpio_set(GPIOA, GPIO4); /* LED off */
		for (i = 0; i < 500000; i++) /* Wait a bit. */
		__asm__("nop");
	}
	
	return 0;
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
