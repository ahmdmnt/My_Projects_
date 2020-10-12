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


/**** Defined Symbolic Constants ****/
/***DIO Pins***/
#define DDR_A 0
#define DDR_B 1
#define DDR_C 2
#define DDR_D 3
/*****************/
#define PIN_A 0
#define PIN_B 1
#define PIN_C 2
#define PIN_D 3
/*****************/
#define PORT_A 0
#define PORT_B 1
#define PORT_C 2
#define PORT_D 3
/*****************/
#define PA0     0
#define PA1     1
#define PA2     2
#define PA3     3
#define PA4     4
#define PA5     5
#define PA6     6
#define PA7     7
/*****************/
#define PB0     0
#define PB1     1
#define PB2     2
#define PB3     3
#define PB4     4
#define PB5     5
#define PB6     6
#define PB7     7
/*****************/
#define PC0     0
#define PC1     1
#define PC2     2
#define PC3     3
#define PC4     4
#define PC5     5
#define PC6     6
#define PC7     7
/*****************/
#define PD0     0
#define PD1     1
#define PD2     2
#define PD3     3
#define PD4     4
#define PD5     5
#define PD6     6
#define PD7     7
/***External Interrupts Pins***/
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3
#define ISC2  0
#define INT0  6
#define INT1  7
#define INT2  5
#define INTF0 6
#define INTF1 7
#define INTF2 5
/***Timer0 Pins***/
#define CS00  0
#define CS01  1
#define CS02  2
#define WGM01 3
#define COM00 4
#define COM01 5
#define WGM00 6
#define FOC0  7
#define TOIE0 0
#define OCIE0 1
#define TOV0  0
#define OCF0  1
/***Timer1 Pins***/
#define WGM10   0
#define WGM11   1
#define FOC1B   2
#define FOC1A   3
#define COM1B0  4
#define COM1B1  5
#define COM1A0  6
#define COM1A1  7
#define CS10    0
#define CS11    1
#define CS12    2
#define WGM12   3
#define WGM13   4
#define ICES1   6
#define ICNC1   7
#define TOIE1   2
#define OCIE1B  3
#define OCIE1A  4
#define TICIE1  5
#define TOV1    2
#define OCF1B   3
#define OCF1A   4
#define ICF1    5
/*****************/
/***ADC Pins***/
#define REFS1   7
#define REFS0   6
#define ADLAR   5
#define MUX4    4
#define MUX3    3
#define MUX2    2
#define MUX1    1
#define MUX0    0
#define ADEN    7
#define ADSC    6
#define ADATE   5
#define ADIF    4
#define ADIE    3
#define ADPS2   2
#define ADPS1   1
#define ADPS0   0
#define ADTS2   7
#define ADTS1   6
#define ADTS0   5
/*****************/

#endif /* DATATYPES_H_ */
