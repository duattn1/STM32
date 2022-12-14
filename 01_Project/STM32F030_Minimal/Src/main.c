/** @file main.c
 *  @brief Definition of main function
 *
 *  This is the source file for main function.
 *
 *  @author duattran
 *  @version V1.0
 *
 * ------------------------------ REVISION HISTORY -----------------------------
 * Dec 12, 2022 - Initialized the main.c file
 *              - Added LED blinking sample with minimum code size
 *              - Added minimal USART sample
 * Dec 13, 2022 - Corrected baudrate number and selected pins for USART sample
 * Dec 14, 2022 - Moved STM32F030F4P6 addresses specification into 
 *              a new header file (stm32f030f4p6.h)
 *              - Added GPIO external interrupt sample
 * -----------------------------------------------------------------------------
 */

/*******************************************************************************
 * 1. Included Files
 ******************************************************************************/
#include "stm32f030f4p6.h"
#include "MAX7219.h"
#include "system_typedef.h"

/*******************************************************************************
 * 2. Object-like Macros
 ******************************************************************************/
/* Peripheral sample enable */
//#define SAMPLE1_GPIO
#define SAMPLE2_GPIO_EXTI
//#define SAMPLE3_USART

/*******************************************************************************
 * 3. Function-like Macros
 ******************************************************************************/

/*******************************************************************************
 * 4. Typedefs: Enumerations, Structures, Unions, Pointers, Others
 ******************************************************************************/

/*******************************************************************************
 * 5. Global, Static, Constant, Extern Variables and Extern Functions
 ******************************************************************************/
int main(void);
void delay(uint32_t count);
void EXTI0_1_ISR(void);
void EXTI2_3_ISR(void);

/* Minimal vector table */
uint32_t *vector_table[] __attribute__((section(".isr_vector"))) = {
    (uint32_t *)SRAM_END, // initial stack pointer
	(uint32_t *)main, // main as Reset_Handler
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
	(uint32_t *)EXTI0_1_ISR,	// EXTI0_1 interrupt ISR
	(uint32_t *)EXTI2_3_ISR		// EXTI2_3 interrupt ISR
	/* and the rest , bla bla */
};

/*******************************************************************************
 * 6. Function Definitions
 ******************************************************************************/
void EXTI0_1_ISR(void)
{
	/* Interrupt handler for EXTI0_1 */
	*EXTI_PR |= 0b1 << 1; // Clear interrupt flag on PA1 (line 1). Flag is cleared by writing a 1 to the bit
	*GPIOA_BSRR |= 0b1 << 4; // Set LED pin (PA4)
}

void EXTI2_3_ISR(void)
{
	/* Interrupt handler for EXTI2_3 */
	*EXTI_PR |= 0b1 << 2; // Clear interrupt flag on PA2 (line 2). Flag is cleared by writing a 1 to the bit
	*GPIOA_BRR |= 0b1 << 4; // Reset LED pin (PA4)
}

/**
  * @brief  The application entry point.
  */
int main(void)
{
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
	*RCC_AHBENR |= 0b1 << 17; // Enable clock for GPIOA

	/* Configure the LED pin (PA4) as output,
	 * and the rest settings as default (push-pull and low speed output, no pull-up/pull-down activated)
	 */
	*GPIOA_MODER |= 0b1 << 8;

	while(1)
	{
			*GPIOA_BSRR |= 0b1 << 4; // Set PA4: turn LED on
			delay(1000000); // Delay 1000000 ticks
			*GPIOA_BRR |= 0b1 << 4; // Reset PA4: turn LED off
			delay(1000000);
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
	*RCC_AHBENR |= 0b1 << 17; // Enable clock for GPIOA

	/*
	 * Configure the LED pin (PA4) as output,
	 * and the rest settings as default (push-pull and low speed output, no pull-up/pull-down activated)
	 */
	*GPIOA_MODER |= 0b1 << 8; // Configure the LED pin (PA4) as output

	/*
	 * Configure PA1 and PA2 as pull-up input.
	 * Default PA1 and PA2 are input.
	 */
	*GPIOA_PUPDR |= (0b01 << 2) | (0b01 << 4); // Select pull-up for PUPDR1[1:0] and PUPDR2[1:0]

	/*
	 * 2. Configure EXTI
	 * - Step 1: Enable clock for SYSCFG
	 * - Step 1.2: Select 1 GPIO line of EXTIx[3:0] bits in SYSCFG_EXTICRx register
	 * - Step 2: For interrupt, configure interrupt mask in EXTI_IMR register
	 * - Step 3: Select interrupt trigger type (falling trigger OR/AND rising trigger) in EXTI_RTSR and EXTI_FTSR
	 */
	*RCC_APB2ENR |= 0b1 << 0; // Enable clock for SYSCFG
	/* PA1 and PA2 are default selections on EXTI1[3:0] and EXTI2[3:0] of SYSCFG_EXTICR1 register */
	*EXTI_IMR |= (0b1 << 1) | (0b1 << 2);
	*EXTI_FTSR |= (0b1 << 1) | (0b1 << 2);

	/*
	 * 3. Enable external interrupt for PA1 and PA2
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

	/* Set priority for EXTI0_1 (PA1) and EXTI2_3 (PA2) interrupt. Default priority is 0 */

	/*
	 * - Enable EXTI0_1 interrupt for pin PA1 (PA1 connects to EXTI Line[1:0] interrupts)
	 * - Enable EXTI2_3 interrupt for pin PA2 (PA2 connects to EXTI Line[3:2] interrupts)
	 * [Notes]
	 * - (0b11111: the mask for max number of STM32F030F4P6 interrupt lines)
	 * - When enable an interrupt in NVIC_ISER, the corresponding bit in NVIC_ICER and NVIC_ISPR is set to 1 to
	 */
	*NVIC_ISER |= 0b1 << (5 & 0b11111); // 5: position of EXTI0_1 interrupt
	*NVIC_ISER |= 0b1 << (6 & 0b11111); // 6: position of EXTI2_3 interrupt

	while(1)
	{

	}

#endif /* SAMPLE2_GPIO_EXTI */

#ifdef  SAMPLE3_USART
	char msg[] = "Hello";

	*RCC_AHBENR |= 1 << 17; // Enable clock for GPIOA
	/* Configure the integrated TX pin (PA2) and RX pin (PA3) of USART1 */
	*GPIOA_MODER |= (0b10 << 4) | (0b10 << 6) ; // select alternate function mode
	/* To enable USART on PA2 and PA3, select AF1 (refer Alternate functions table in datasheet) */
	*GPIOA_AFRL |= (0b0001 << 8) | (0b0001 << 12); // Set AFSEL9[3:0] and AFSEL10[3:0] bits as 0x01


	/* Configure USART */
	*RCC_APB2ENR |= 1 << 14; // Enable clock for USART1
	/* Default settings USART are
	 * - 8 data bits
	 * - parity control disabled
	 * - Oversampling by 16 mode
	 * - 1 stop bit
	 */

	/* When select oversampling by 16, BRR = USARTDIV = f(CK) / Tx/Rx baud */
	*USART1_BRR = 833; // (8000000/9600) Desired baud rate is 9600
	*USART1_CR1 = (1 << 3) | (1 << 0); // Enable transmission and USART
	
	/* Send string "Hello" via USART */
	for(int i = 0; i < 5; i++)
	{
		while(!(*USART1_ISR & (1 << 7))); // Check TXE flag if Transmit data register is empty
		*USART1_TDR = msg[i];
	}
#endif /* SAMPLE3_USART */

}

/**
  * @brief  Delay MCU
  */
void delay(uint32_t count)
{
	while(count--);
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
