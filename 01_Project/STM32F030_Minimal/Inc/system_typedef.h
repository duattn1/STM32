/** @file  system_typedef.h
 *  @brief Declaration of types used in project
 *
 *  This is the header file for the type declaration
 *
 *  @author duattran
 *  @version V1.0
 */

#ifndef SYSTEM_TYPEDEF_H
#define SYSTEM_TYPEDEF_H

/*******************************************************************************
 * 1. Included Files
 ******************************************************************************/

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
typedef enum
{
	false = 0x00,
	true = 0x01
} bool;

typedef enum
{
	LOW = 0x00,
	HIGH = 0x01
} state_t;

/** 4.2. Structure Typedef ****************************************************/

/** 4.3. Union Typedef ********************************************************/

/** 4.4. Pointer Typedef ******************************************************/

/** 4.5. Other Typedef ********************************************************/
typedef unsigned long uint32_t;
typedef unsigned char byte;

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

#endif /* SYSTEM_TYPEDEF_H */

/** End of File ***************************************************************/
