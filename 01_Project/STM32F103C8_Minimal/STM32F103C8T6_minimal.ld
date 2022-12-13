/** @file STM32F103C8T6_minimal.ld
 *  @brief STM32F103C8T6 linker file
 *
 *  This is the linker file for STM32F103C8T6 MCU.
 *
 *  @author duattran
 *  @version V1.0
 *
 * ------------------------------ REVISION HISTORY -----------------------------
 * Dec 13, 2022 - Initialized the linker file
 *              
 * -----------------------------------------------------------------------------
 */

/* Entry Point */
ENTRY(main)

/* Memories definition */
MEMORY
{
    SRAM    (xrw)   : ORIGIN = 0x20000000, LENGTH = 20K
    FLASH   (rx)    : ORIGIN = 0x08000000, LENGTH = 64K
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