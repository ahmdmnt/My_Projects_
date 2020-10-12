/**********************************************************************************************
 * DIO.h
 * 
 *		**DIO - Driver**
 *      Designed for AVR ATmega16 Microcontroller
 *
 *  Created on: Sep 6, 2020
 *      Author: Ahmed Montasser
 **********************************************************************************************
 * > When Using this Module :-
 * -----------------------------
 * 1. Set the port_name Value with below defines only:
 *      -DDR_A      -DDR_C      -DDR_B      -DDR_D
 *      -PIN_A      -PIN_C      -PIN_B      -PIN_D
 *      -PORT_A     -PORT_C     -PORT_B     -PORT_D
 * 
 * 2. Set the pin_name Value with below defines only:
 *      -PA0  -PA1  -PA2  -PA3  -PA4  -PA5  -PA6  -PA7
 *      -PB0  -PB1  -PB2  -PB3  -PB4  -PB5  -PB6  -PB7
 *      -PC0  -PC1  -PC2  -PC3  -PC4  -PC5  -PC6  -PC7
 *      -PD0  -PD1  -PD2  -PD3  -PD4  -PD5  -PD6  -PD7
 * 
 * 3. Set the direction Value with below defines only:
 *      -INPUT_PIN         -OUT_PIN
 *      -INPUT_PORT         -OUT_PORT
 * 
 * 4. Set the "value" Value with below defines only:
 *      -HIGH              -LOW
 * 
 **********************************************************************************************/

#ifndef DIO_H_
#define DIO_H_

/** Configuration Parameters ***************************************************/
/*** Defined Symbolic Constants ******/
#define INPUT_PIN 0
#define OUTPUT_PIN 1
#define INPUT_PORT 0
#define OUTPUT_PORT 1
// #define GROUP_OF_2PINS 0b00000011    // #define GROUP_OF_3PINS 0b00000111    // #define GROUP_OF_4PINS 0b00001111   
// #define GROUP_OF_5PINS 0b00011111    // #define GROUP_OF_6PINS 0b00111111    // #define GROUP_OF_7PINS 0b01111111
/*** Static Configurations ******/    /* Edited By Developer */
/*****************************************************************************/

/** Used Directories *********************************************************/
#include "datatypes.h"
#include "macros.h"
#include "registers.h"
/*****************************************************************************/

/** Externed Global Variables ************************************************/
/*****************************************************************************/

/** Variables Declaration ****************************************************/
/*****************************************************************************/

/** Function Prototypes ******************************************************/

/*** Description:-
 * Adjust the DDR_x Registers for Desired PXX with needed direction */
void  __DIO_setPinDirection(uint8 port_name,uint8 pin_name,uint8 direction);

/*** Description:-
 * Enable Internal Pullup Resistor for the Input Pin */
void  __DIO_enableInternalPullupResistance(uint8 port_name,uint8 pin_name);

/*** Description:-
 * Output a Digital Value over the Output Pin */
void  __DIO_writeOutputPinValue(uint8 port_name,uint8 pin_name,uint8 value);

/*** Description:-
 * Read and fetch the Digital Value from a Pin */
uint8 __DIO_readInputPinValue(uint8 port_name,uint8 pin_name);

/*** Description:-
 * Toggle the Value of Output Pin */
void  __DIO_toggleOutputPinValue(uint8 port_name,uint8 pin_name);

/*** Description:-
 * Adjust the DDR_x Registers for Whole PORT with needed direction */
void  __DIO_setPortDirection(uint8 port_name, uint8 direction);

/*** Description:-
 * Enable Internal Pullup Resistor for whole PORT Input Pins */
void  __DIO_enablePortInternalPullupResistance(uint8 port_name);

/*** Description:-
 * Output a Digital Values over PORT Output Pins */
void  __DIO_writeOutputPortValue(uint8 port_name,uint8 value);

/*** Description:-
 * Read and fetch the Digital Values from PORT Pins */
uint8 __DIO_readInputPortValue(uint8 port_name);

// void  __DIO_setPinGroupDirection(uint8 port_name, uint8 pins_mask, uint8 direction);
// void  __DIO_enablePinGroupInternalPullupResistance(uint8 port_name, uint8 pins_mask);
// void  __DIO_writeOutputPinGroupValue(uint8 port_name, uint8 pins_mask, uint8 value);
// uint8 __DIO_readInputPinGroupValue(uint8 port_name, uint8 pins_mask);
/*****************************************************************************/

#endif /* DIO_H_ */