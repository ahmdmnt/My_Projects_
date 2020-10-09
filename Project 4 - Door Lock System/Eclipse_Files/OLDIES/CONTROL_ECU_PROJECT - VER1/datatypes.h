/*****************************************************************************
 * datatypes.h
 *  ** Common - Platform Types Abstraction **
 *     -----------------------------------
 *		File Contain user-defined data types for coding portability,
 *      Designed for AVR ATmega16 Microcontroller
 *
 *  Created on: Sep 6, 2020
 *      Author: Ahmed Montasser
 *****************************************************************************/

#ifndef DATATYPES_H_
#define DATATYPES_H_

/* Boolean Data Type */
typedef unsigned char bool;

/* Boolean Values */
#ifndef FALSE
#define FALSE       (0u)
#endif

#ifndef TRUE
#define TRUE        (1u)
#endif

#ifndef HIGH
#define HIGH        (1u)
#endif

#ifndef LOW
#define LOW         (0u)
#endif


typedef unsigned char       uint8;      /*           0 .. 255             */
typedef signed char         sint8;      /*        -128 .. +127            */

typedef unsigned short     uint16;      /*           0 .. 65535           */
typedef signed short       sint16;      /*      -32768 .. +32767          */

typedef unsigned int       uint32;      /*           0 .. 4294967295      */
typedef signed int         sint32;      /* -2147483648 .. +2147483647     */

typedef unsigned long long uint64;      /*       0..18446744073709551615  */
typedef signed long long   sint64;  

typedef float  float32;
typedef double float64;


#endif /* DATATYPES_H_ */
