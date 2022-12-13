/** @file MAX7219.h
 *  @brief Declaration of MAX7219 control function
 *
 *  This is the header file for the definition of MAX7219 control function.
 *
 *  @author duattran
 *  @version V1.0
 */

#ifndef MAX7219_H
#define MAX7219_H

/*******************************************************************************
 * 1. Included Files
 ******************************************************************************/
#include "system_typedef.h"

/*******************************************************************************
 * 2. Object-like Macros
 ******************************************************************************/

/*******************************************************************************
 * 3. Function-like Macros
 ******************************************************************************/

/*******************************************************************************
 * 4. Typedefs: Enumerations, Structures, Unions, Pointers, Others
 ******************************************************************************/
/** 4.1. Enumeration Typedef **************************************************/
typedef enum DecodeModes
{
    DecodeMode_NoDecode     = 0x00,
    DecodeMode_Digit0       = 0x01,
    DecodeMode_Digit1       = 0x02,
    DecodeMode_Digit2       = 0x04,
    DecodeMode_Digit3       = 0x08,
    DecodeMode_Digit4       = 0x10,
    DecodeMode_Digit5       = 0x20,
    DecodeMode_Digit6       = 0x40,
    DecodeMode_Digit7       = 0x80,
    DecodeMode_AllDigits    = 0xFF
} DecodeMode_t;

typedef enum Intensities
{
    Intensity_Level0    = 0x00,
    Intensity_Level1    = 0x01,
    Intensity_Level2    = 0x02,
    Intensity_Level3    = 0x03,
    Intensity_Level4    = 0x04,
    Intensity_Level5    = 0x05,
    Intensity_Level6    = 0x06,
    Intensity_Level7    = 0x07,
    Intensity_Level8    = 0x08,
    Intensity_Level9    = 0x09,
    Intensity_Level10   = 0x0A,
    Intensity_Level11   = 0x0B,
    Intensity_Level12   = 0x0C,
    Intensity_Level13   = 0x0D,
    Intensity_Level14   = 0x0E,
    Intensity_Level15   = 0x0F
} Intensity_t;

typedef enum ScanLimits
{
    ScanLimit_Digit0    = 0x00,
    ScanLimit_Digit0To1 = 0x01,
    ScanLimit_Digit0To2 = 0x02,
    ScanLimit_Digit0To3 = 0x03,
    ScanLimit_Digit0To4 = 0x04,
    ScanLimit_Digit0To5 = 0x05,
    ScanLimit_Digit0To6 = 0x06,
    ScanLimit_Digit0To7 = 0x07
} ScanLimit_t;

typedef enum ShutdownModes
{
    ShutdownMode_Shutdown           = 0x00,
    ShutdownMode_NormalOperation    = 0x01
} ShutdownMode_t;

typedef enum DisplayTestModes
{
    NormalOperation = 0x00,
    TestMode        = 0x01
} DisplayTestMode_t;

typedef enum Digits
{
    Digit_0 = 0x01,
    Digit_1 = 0x02,
    Digit_2 = 0x03,
    Digit_3 = 0x04,
    Digit_4 = 0x05,
    Digit_5 = 0x06,
    Digit_6 = 0x07,
    Digit_7 = 0x08
} Digit_t;

typedef enum Characters
{
    Character_Zero  = 0x00,
    Character_One   = 0x01,
    Character_Two   = 0x02,
    Character_Three = 0x03,
    Character_Four  = 0x04,
    Character_Five  = 0x05,
    Character_Six   = 0x06,
    Character_Seven = 0x07,
    Character_Eight = 0x08,
    Character_Nine  = 0x09,
    Character_Dash  = 0x0A,
    Character_E     = 0x0B,
    Character_H     = 0x0C,
    Character_L     = 0x0D,
    Character_P     = 0x0E,
    Character_Blank = 0x0F
} Character_t;

typedef enum Segments
{
    Segment_DP  = 0x80,
    Segment_A   = 0x40,
    Segment_B   = 0x20,
    Segment_C   = 0x10,
    Segment_D   = 0x08,
    Segment_E   = 0x04,
    Segment_F   = 0x02,
    Segment_G   = 0x01
} Segment_t;

/** 4.2. Structure Typedef ****************************************************/

/** 4.3. Union Typedef ********************************************************/

/** 4.4. Pointer Typedef ******************************************************/

/** 4.5. Other Typedef ********************************************************/

/*******************************************************************************
 * 5. Global, Static, External Variables and External Functions
 ******************************************************************************/
/** 5.1. Variables ************************************************************/
extern char m_csPin;

/** 5.2. Functions ************************************************************/
extern void digitalWrite(char pin, state_t state);

/*******************************************************************************
 * 6. Function Definitions
 ******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/** 6.1. Static Functions *****************************************************/

/** 6.2. Global Functions *****************************************************/
void initialize(void);
void setDecodeMode(DecodeMode_t mode);
void setIntensity(Intensity_t intensity);
void setScanLimit(ScanLimit_t limit);
void setShutdownMode(ShutdownMode_t mode);
void setDisplayTestMode(DisplayTestMode_t mode);
void writeDigitC(Digit_t digit, Character_t character, bool decimalPoint); //duat bool decimalPoint = false);
void writeDigit(Digit_t digit, Segment_t segment);
void write(byte address, byte value);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* MAX7219_H */

/** End of File ***************************************************************/
