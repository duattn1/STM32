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
 *              - Added minimal SPI sample
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
//#define SAMPLE_USART
//#define SAMPLE_SPI

/*******************************************************************************
 * 3. Function-like Macros
 ******************************************************************************/

/*******************************************************************************
 * 4. Typedefs: Enumerations, Structures, Unions, Pointers, Others
 ******************************************************************************/

/*******************************************************************************
 * 5. Global, Static, Constant, Extern Variables and Extern Functions
 ******************************************************************************/
char m_csPin = 5; // SCK pin of SPI1 is PA5

int main(void);
void delay(uint32_t count);
void digitalWrite(char pin, state_t state); // function porting for Arduino library

/* Minimal vector table */
uint32_t *vector_table[] __attribute__((section(".isr_vector"))) = {
    (uint32_t *)SRAM_END, // initial stack pointer
	(uint32_t *)main // main as Reset_Handler
};

/*******************************************************************************
 * 6. Function Definitions
 ******************************************************************************/
/**
  * @brief  The application entry point.
  */
int main(void)
{
	char msg[] = "Hello";

#ifdef  SAMPLE1_GPIO
	*RCC_AHBENR |= 1 << 17; // Enable clock for GPIOA
	/* Configure the integrated LED pin (PA4) as output*/
	*GPIOA_MODER |= 1 << (4*2); // set MODER4[1:0] bits as 0x01
	while(1)
	{
			*GPIOA_BSRR |= 1 << 4; // Set PA4
			delay(1000000); // Delay 1000000 ticks
			*GPIOA_BRR |= 1 << 4; // Reset PA4
			delay(1000000);
	}
#endif /* SAMPLE1_GPIO */

#ifdef  SAMPLE2_GPIO_EXTI
	*RCC_AHBENR |= 0b1 << 17; // Enable clock for GPIOA
	/* Configure the LED pin (PA4) as output*/
	*GPIOA_MODER |= 0b1 << 8; // set MODER4[1:0] bits as 0x01

	/* Configure PA1 and PA2 as pull-up input; Enable external interrupt for these pins
	 * Default PA1 and PA2 are input, so that no need to update MODER1[1:0] and MODER2[1:0] bits
	 */
	*GPIOA_PUPDR |= (0b01 << 2) | (0b01 << 4); // Select pull-up for PUPDR1[1:0] and PUPDR2[1:0]

	//0xE000E100 NVICSER0 register

	while(1)
	{

	}
#endif /* SAMPLE2_GPIO_EXTI */

#ifdef  SAMPLE_USART
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
#endif /* SAMPLE_USART */

#ifdef  SAMPLE_SPI
	/* Configure the integrated SCK pin (PA5), MISO pin (PA6) and MOSI pin (PA7) of SPI1 */
	*GPIOA_MODER |= (0x02 << (5*2)) | (0x02 << (6*2)) | (0x02 << (7*2)) ; // select alternate function mode
	/* To enable USART on PA5, PA6 and PA7, select AF0 (refer Alternate functions table in datasheet)
	 * Default value is AF0, so that no need to configure GPIOA_AFRL or GPIOA_AFRH registers
	 */

	*RCC_APB2ENR |= 1 << 12; // Enable clock for SPI1
	/* Configure SPI master
	 * CPOL and CPHA at zero (rising first edge)
	 */
	*SPI1_CR1 |= 1 << 2; // Master mode
	*SPI1_CR1 |= 0x07 << 3;/*, BR: fPCLK/256 (due to C27 on the board, SPI_CLK is
			set to the minimum) */
//	*SPI1_CR2 = SPI_CR2_SSOE | SPI_CR2_RXNEIE | SPI_CR2_FRXTH
//	| SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0; /* Slave select output enabled, RXNE IT, 8-bit Rx fifo */
	*SPI1_CR1 |= 1 << 6; // enable SPI

#endif /* SAMPLE_SPI */

	while (1)
	{

	}
}

/**
  * @brief  Delay MCU
  */
void delay(uint32_t count)
{
	while(count--);
}

/**
  * @brief  Porting function for Arduino library, ONLY for GPIOA of STM32F030
  */
void digitalWrite(char pin, state_t state)
{
	if(LOW == state)
	{
		*GPIOA_BRR |= 1 << pin; // reset <pin>
	} else
	{
		*GPIOA_BSRR |= 1 << pin; // set <pin>
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/** End of File ***************************************************************/
