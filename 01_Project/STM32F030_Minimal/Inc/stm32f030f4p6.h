/** @file  stm32f030f4p6
 *  @brief STM320F030F4P6 addresses specification
 *
 *  This is the header file for STM320F030F4P6 addresses specification
 *
 *  @author duattran
 *  @version V1.0
 */

#ifndef STM32F030F4P6_H
#define STM32F030F4P6_H

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
#define GPIOA_OTYPER	((uint32_t*)(GPIOA_BASE + 0x04))
#define GPIOA_OSPEEDR	((uint32_t*)(GPIOA_BASE + 0x08))
#define GPIOA_PUPDR		((uint32_t*)(GPIOA_BASE + 0x0C))
#define GPIOA_IDR		((uint32_t*)(GPIOA_BASE + 0x10))
#define GPIOA_ODR		((uint32_t*)(GPIOA_BASE + 0x14))
#define GPIOA_BSRR		((uint32_t*)(GPIOA_BASE + 0x18))
#define GPIOA_LCKR		((uint32_t*)(GPIOA_BASE + 0x1C))
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

/*******************************************************************************
 * 3. Function-like Macros
 ******************************************************************************/

/*******************************************************************************
 * 4. Typedefs: Enumerations, Structures, Unions, Pointers, Others
 ******************************************************************************/
/** 4.1. Enumeration Typedef **************************************************/

/** 4.2. Structure Typedef ****************************************************/

/** 4.3. Union Typedef ********************************************************/

/** 4.4. Pointer Typedef ******************************************************/

/** 4.5. Other Typedef ********************************************************/


/*******************************************************************************
 * 5. Global, Static, External Variables and External Functions
 ******************************************************************************/
/** 5.1. Variables ************************************************************/

/** 5.2. Functions ************************************************************/

/*******************************************************************************
 * 6. Function Definitions
 ******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/** 6.1. Static Functions *****************************************************/

/** 6.2. Global Functions *****************************************************/

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* STM32F030F4P6_H */

/** End of File ***************************************************************/
