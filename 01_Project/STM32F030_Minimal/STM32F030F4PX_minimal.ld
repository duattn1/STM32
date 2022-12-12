/** @file STM32F030F4PX_minimal.ld
 *  @brief STM32F030 linker file
 *
 *  This is the linker file for STM32F030F4P6 MCU.
 *
 *  @author duattran
 *  @version V1.0
 *
 * ------------------------------ REVISION HISTORY -----------------------------
 * Dec 12, 2022 - Initialize the linker file
 *              
 * -----------------------------------------------------------------------------
 */

/* Entry Point */
ENTRY(main)

/* Memories definition */
MEMORY
{
    SRAM    (xrw)   : ORIGIN = 0x20000000, LENGTH = 4K
    FLASH   (rx)    : ORIGIN = 0x08000000, LENGTH = 16K
}

/* Sections */
SECTIONS
{
    /* Program code into FLASH */
    .text : ALIGN(4)
    {
        *(.isr_vector) /* Vector table */
        *(.text) /* Program code */
        KEEP(*(.isr_vector))
    } >FLASH

    /* Initialized global and static variables into SRAM */
    .data :
    {
        *(.data)
    } >SRAM
}