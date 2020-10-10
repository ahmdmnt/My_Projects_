/***********************************************************************************************
 * keypad.h
 * 
 *		**keypad - Driver**
 *      Designed for AVR ATmega16 Microcontroller
 *
 *  Created on: Sep 6, 2020
 *      Author: Ahmed Montasser
 ***********************************************************************************************
  * > When Using this Module :-
 * -----------------------------
 * 1. Set Keypad pins all in one DIO PORT.
 *      - Rows from Px0 to Px3
 *      - Cols from Px4 to Px7
 * 
 **********************************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "datatypes.h"
#include "macros.h"
#include "registers.h"

/** Configuration Parameters ***************************************************/
/*** Static Configurations ******/     /** Edited By Developer **/
#define N_col 4
#define N_row 4
#define KEYPAD_PORT_OUT PORTA
#define KEYPAD_PORT_IN  PINA
#define KEYPAD_PORT_DIR DDRA 
/*****************************************************************************/


/** Function Prototypes ***************************************************/

/*
 * Function responsible for getting the pressed keypad key
 */
uint8 _KEYPAD_getCurrentPressedKey(void);
/*****************************************************************************/
#endif /* KEYPAD_H_ */
