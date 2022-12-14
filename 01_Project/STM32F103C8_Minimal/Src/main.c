/** @file main.c
 *  @brief Definition of main function
 *
 *  This is the source file for main function.
 *
 *  @author duattran
 *  @version V1.0
 *
 * ------------------------------ REVISION HISTORY -----------------------------
 * Dec 13, 2022 - Initialized the main.c file
 *              - Added LED blinking sample with minimum code size
 *
 * -----------------------------------------------------------------------------
 */

/*******************************************************************************
 * 1. Included Files
 ******************************************************************************/

/*******************************************************************************
 * 2. Object-like Macros
 ******************************************************************************/
/* Memory and peripheral start addresses */
#define FLASH_BASE			0x08000000
#define SRAM_BASE			0x20000000
#define PERIPH_BASE			0x40000000
#define APB1PERIPH_BASE		(PERIPH_BASE + 0x00000000)
#define APB2PERIPH_BASE		(PERIPH_BASE + 0x00010000)
#define AHBPERIPH_BASE		(PERIPH_BASE + 0x00018000)

/* Work out end of RAM address as initial stack pointer(specific of a given STM32 MCU */
#define SRAM_SIZE 20*1024 // STM32F103C8T6 has 20 KB of RAM
#define SRAM_END (SRAM_BASE + SRAM_SIZE)

/* RCC peripheral addresses */
#define RCC_BASE	(AHBPERIPH_BASE + 0x00009000)
#define RCC_AHBENR	((uint32_t*)(RCC_BASE + 0x14))
#define RCC_APB2ENR	((uint32_t*)(RCC_BASE + 0x18))


/* GPIOC peripheral addresses */
#define GPIOC_BASE		(APB2PERIPH_BASE + 0x00001000) // GPIOA connects to APB2 bus
#define GPIOC_CRL		((uint32_t*)(GPIOC_BASE + 0x00))
#define GPIOC_CRH		((uint32_t*)(GPIOC_BASE + 0x04))
#define GPIOC_IDR		((uint32_t*)(GPIOC_BASE + 0x08))
#define GPIOC_ODR		((uint32_t*)(GPIOC_BASE + 0x0C))
#define GPIOC_BSRR		((uint32_t*)(GPIOC_BASE + 0x10))
#define GPIOC_BRR		((uint32_t*)(GPIOC_BASE + 0x14))
#define GPIOC_LCKR		((uint32_t*)(GPIOC_BASE + 0x08))

/* USART peripheral addresses */
#define USART1_BASE		(APB2PERIPH_BASE + 0x00003800) // 0x4001 3800
#define USART1_CR1		((uint32_t*)(USART1_BASE + 0x00))
#define USART1_CR2		((uint32_t*)(USART1_BASE + 0x04))
#define USART1_BRR		((uint32_t*)(USART1_BASE + 0x0C))
#define USART1_ISR		((uint32_t*)(USART1_BASE + 0x1C))
#define USART1_ICR		((uint32_t*)(USART1_BASE + 0x20))
#define USART1_TDR		((uint32_t*)(USART1_BASE + 0x28))
#define USART_ISR_TXE		(1 << 7) // mask for TXE bit of USART_ISR register


/* Peripheral sample enable */
#define SAMPLE_GPIO
//#define SAMPLE_USART

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
void delay(uint32_t count);

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
#ifdef  SAMPLE_GPIO
	*RCC_APB2ENR |= 1 << 4; // Enable clock for GPIOC

	/* Configure LED pin (PC13) as open-drain (default) output, 10Mhz speed */
	*GPIOC_CRH |= 0b01 << 20; // set MODE13[1:0] bits as 0b01

	while(1)
	{
			*GPIOC_BSRR |= 1 << 13; // Set PC13
			delay(1000000); // Delay 1000000 ticks
			*GPIOC_BRR |= 1 << 13; // Reset PC13
			delay(1000000);
	}
#endif /* SAMPLE_GPIO */

#ifdef  SAMPLE_USART
	/* Configure TX pin (PA9) and RX pin (PA10) of USART1 as alternate function mode
	 * USART1 pins are selected via USART1_REMAP bit in AFIO_MAPR register, default pins are PA9 and PA10.
	 * The other selection is PB6 (TX) and PB7 (RX) */
	*GPIOC_CRH |= (0b01 << 4) | (0b10 << 6); // PA9: set MODE9[1:0] bits as 0b01 and CNF9[1:0] as 0b10
	*GPIOC_CRH |= (0b01 << 8) | (0b10 << 10); // PA10: set MODE10[1:0] bits as 0b01 and CNF10[1:0] as 0b10
//	/* To enable USART on PA9 and PA10, select AF1 (refer Alternate functions table in datasheet) */
//	*GPIOA_AFRL |= (0x01 << 8) | (0x01 << 12); // Set AFSEL9[3:0] and AFSEL10[3:0] bits as 0x01


	/* Configure USART */
	*RCC_APB2ENR |= 1 << 14; // Enable clock for USART1
	/* Configure word length, number of stop bit, parity mode and oversampling mode.
	 * After device resets, default settings are
	 * - 8 data bits
	 * - parity control disabled
	 * - Oversampling by 16 mode
	 * - 1 stop bit
	 */
//	*USART1_CR1 &= ~((0x00 << 12) | (0x00 << 28)); // Set M0 and M1 bit as 0 => 8 data bits
//	*USART1_CR1 &= ~(0x00 << 10); // Set PCE bit as 0 => parity control disabled
//	*USART1_CR1 &= ~(0x00 << 15); // Set OVER8 bit as 0 => Oversampling by 16
//	*USART1_CR2 &= ~(0x00 << 12); // Set STOP[1:0] as 0x00 => 1 stop bit

	/* When select oversampling by 16, BRR = USARTDIV = f(CK) / Tx/Rx baud */
	*USART1_BRR = 5000; // (48000000/9600) Desired baud rate is 9600

//	*USART1_CR1 |= 1 << 3; // Enable transmission  via TE bit
////	*USART1_CR1 |= 1 << 2; // Enable reception via RE bit
//	*USART1_CR1 |= 1 << 0; // Enable USART via UE bit
	*USART1_CR1 = (1 << 3) | (1 << 0);
	
	while(!(*USART1_ISR & (1 << 7)));
	*USART1_TDR = 'h';
	
	//After writing the last data into the USART_TDR register, wait until TC=1. This indicates
	//that the transmission of the last frame is complete
#endif /* SAMPLE_USART */

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
