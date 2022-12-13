/** @file MAX7219.c
 *  @brief Definition of MAX7219 control function
 *
 *  This is the source file for MAX7219 control
 *
 *  @author duattran
 *  @version V1.0
 *
 * ------------------------------ REVISION HISTORY -----------------------------
 * Dec 13, 2022 - Ported MAX7219 library from Arduino project
 *
 * -----------------------------------------------------------------------------
 */

/*******************************************************************************
 * 1. Included Files
 ******************************************************************************/
#include "MAX7219.h"

/*******************************************************************************
 * 2. Object-like Macros
 ******************************************************************************/
#define REG_NO_OP           0x00
#define REG_DIGIT_0         0x01
#define REG_DIGIT_1         0x02
#define REG_DIGIT_2         0x03
#define REG_DIGIT_3         0x04
#define REG_DIGIT_4         0x05
#define REG_DIGIT_5         0x06
#define REG_DIGIT_6         0x07
#define REG_DIGIT_7         0x08
#define REG_DECODE_MODE     0x09
#define REG_INTENSITY       0x0A
#define REG_SCAN_LIMIT      0x0B
#define REG_SHUTDOWN        0x0C
#define REG_DISPLAY_TEST    0x0F

/*******************************************************************************
 * 3. Function-like Macros
 ******************************************************************************/

/*******************************************************************************
 * 4. Typedefs: Enumerations, Structures, Unions, Pointers, Others
 ******************************************************************************/

/*******************************************************************************
 * 5. Global, Static, Constant, Extern Variables and Extern Functions
 ******************************************************************************/
extern void delay(uint32_t count);

/*******************************************************************************
 * 6. Function Definitions
 ******************************************************************************/
/**
  * @brief  Initialize SPI to drive MAX7219.
  */
void initialize(void)
{
	// Wait a little to allow MAX7219 to see a correct logic level on CS pin.
    delay(1);
    
//duat    // Configure SPI.
//    SPI.begin();
//    SPI.setBitOrder(MSBFIRST);
//    SPI.setDataMode(SPI_MODE0);
//    SPI.setClockDivider(SPI_CLOCK_DIV4);
}

/**
  * @brief  Set MAX7219 decode mode.
  */
void setDecodeMode(DecodeMode_t mode)
{
    write(REG_DECODE_MODE, mode);
}

/**
  * @brief  Set MAX7219 intensity.
  */
void setIntensity(Intensity_t intensity)
{
    write(REG_INTENSITY, intensity);
}

/**
  * @brief  Set MAX7219 scan limit.
  */
void setScanLimit(ScanLimit_t limit)
{
    write(REG_SCAN_LIMIT, limit);
}

/**
  * @brief  Set MAX7219 shutdown mode.
  */
void setShutdownMode(ShutdownMode_t mode)
{
    write(REG_SHUTDOWN, mode);
}

/**
  * @brief  Set MAX7219 display test mode.
  */
void setDisplayTestMode(DisplayTestMode_t mode)
{
    write(REG_DISPLAY_TEST, mode);
}

/**
  * @brief  Write character on digit.
  *
  * @param	digit		    Digit to write.
  * @param	character	    Character to write.
  * @param   decimalPoint    Display decimal point if true.
  */
void writeDigitC(Digit_t digit, Character_t character, bool decimalPoint)
{
    byte value = character;
    if (decimalPoint)
    {
        // If decimal point must be switched on.
        value |= Segment_DP;
    }
    write(digit, value);
}

/**
  * @brief Set segment(s) on digit.
  *
  * @param	digit	Digit to write.
  * @param	segment	Segment(s) to set.
  */
void writeDigit(Digit_t digit, Segment_t segments)
{
    write(digit, segments);
}

/**
  * @brief Write value into MAX7219 register.
  *
  * @param	address	Register address.
  * @param	value	Value to write.
  */
void write(byte address, byte value)
{
    // Reset chip select pin to select the device.
    digitalWrite(m_csPin, LOW);
//duat    // Transmit data to the device, register address and value.
//    SPI.transfer(address);
//    SPI.transfer(value);
    // Set chip select pin to valid data onto the device.
    digitalWrite(m_csPin, HIGH);
}

/** End of File ***************************************************************/
