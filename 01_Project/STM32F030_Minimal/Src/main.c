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
 *              text    data    bss     dec     hex     filename
 *              142     0       0       142     8e      STM32F030_Minimal.elf
 *              - Added minimal USART sample
 * Dec 13, 2022 - Corrected baudrate number and selected pins for USART sample
 *              - Added minimal SPI sample
 *              
 * -----------------------------------------------------------------------------
 */

/*******************************************************************************
 * 1. Included Files
 ******************************************************************************/
#include "MAX7219.h"
#include "system_typedef.h"

/*******************************************************************************
 * 2. Object-like Macros
 ******************************************************************************/
/* Memory and peripheral start addresses */
#define FLASH_BASE			0x08000000
#define SRAM_BASE			0x20000000
#define PERIPH_BASE			0x40000000
#define APBPERIPH_BASE		(PERIPH_BASE + 0x00000000)
#define AHB1PERIPH_BASE		(PERIPH_BASE + 0x00020000)
#define AHB2PERIPH_BASE		(PERIPH_BASE + 0x08000000)

/* Work out end of RAM address as initial stack pointer(specific of a given STM32 MCU */
#define SRAM_SIZE 4*1024 // STM32F030F4P6 has 4 KB of RAM
#define SRAM_END (SRAM_BASE + SRAM_SIZE)

/* RCC peripheral addresses applicable to GPIOA */
#define RCC_BASE	(AHB1PERIPH_BASE + 0x00001000)
#define RCC_AHBENR	((uint32_t*)(RCC_BASE + 0x14))
#define RCC_APB2ENR	((uint32_t*)(RCC_BASE + 0x18))


/* GPIOA peripheral addresses */
#define GPIOA_BASE		(AHB2PERIPH_BASE + 0x00000000) // All GPIO port, including GPIOA, connect to AHB2 bus
#define GPIOA_MODER		((uint32_t*)(GPIOA_BASE + 0x00))
//#define GPIOA_OTYPER	((uint32_t*)(GPIOA_BASE + 0x04))
//#define GPIOA_OSPEEDR	((uint32_t*)(GPIOA_BASE + 0x08))
//#define GPIOA_PUPDR		((uint32_t*)(GPIOA_BASE + 0x0C))
//#define GPIOA_IDR		((uint32_t*)(GPIOA_BASE + 0x10))
//#define GPIOA_ODR		((uint32_t*)(GPIOA_BASE + 0x14))
#define GPIOA_BSRR		((uint32_t*)(GPIOA_BASE + 0x18))
//#define GPIOA_LCKR		((uint32_t*)(GPIOA_BASE + 0x1C))
#define GPIOA_AFRL		((uint32_t*)(GPIOA_BASE + 0x20))
#define GPIOA_AFRH		((uint32_t*)(GPIOA_BASE + 0x24))
#define GPIOA_BRR		((uint32_t*)(GPIOA_BASE + 0x28))

/* USART peripheral addresses */
#define USART1_BASE		(APBPERIPH_BASE + 0x00013800) // 0x4001 3800
#define USART1_CR1		((uint32_t*)(USART1_BASE + 0x00))
#define USART1_CR2		((uint32_t*)(USART1_BASE + 0x04))
#define USART1_BRR		((uint32_t*)(USART1_BASE + 0x0C))
#define USART1_ISR		((uint32_t*)(USART1_BASE + 0x1C))
#define USART1_ICR		((uint32_t*)(USART1_BASE + 0x20))
#define USART1_TDR		((uint32_t*)(USART1_BASE + 0x28))
#define USART_ISR_TXE		(1 << 7) // mask for TXE bit of USART_ISR register

/* SPI peripheral addresses */
#define SPI1_BASE		(APBPERIPH_BASE + 0x00013000) // 0x4001 3000
#define SPI1_CR1		((uint32_t*)(SPI1_BASE + 0x00))
#define SPI1_CR2		((uint32_t*)(SPI1_BASE + 0x04))


/* Peripheral sample enable */
//#define SAMPLE_GPIO
#define SAMPLE_USART
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

#ifdef  SAMPLE_GPIO
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
#endif /* SAMPLE_GPIO */

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
	*USART1_BRR = 833; // (48000000/9600) Desired baud rate is 9600
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
