/***********************************************************************************************
 * external_interrupt.h
 * 
 *		**External Interrupts - Driver**
 *      Designed for AVR ATmega16 Microcontroller
 *
 *  Created on: Sep 6, 2020
 *      Author: Ahmed Montasser
 ***********************************************************************************************
 * > When Using this Module :-
 * -----------------------------
 * 1. Define the needed interrupt to allow its code, otherwise it will be disbaled:
 *      #define _INT0
 *      #define _INT1
 *      #define _INT2
 * 
 * 2. Write the Desired ISR Code in a C created Function of your own, in the following format:
 *      void FUNCTION_NAME(void)
 *          { ...Function Code ... }
 * 
 * 3. Send the created function name to the driver via:
 *      __INTX_setISRCallBackFuncPointer(<FUNCTION_NAME>);                (where X= 0, 1, 2)
 * 
 * 4. Set the Sense Control Value with below defines only:
 *      - LOW_LOGIC             - LOGIC_CHANGE
 *      - RISING_EDGE           - FALLING_EDGE
 * 
 **********************************************************************************************/

#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_


/** Configuration Parameters ***************************************************/
/*** Defined Symbolic Constants ******/
#define LOW_LOGIC       0
#define LOGIC_CHANGE    1
#define FALLING_EDGE    2
#define RISING_EDGE     3
/*** Static Configurations ******/    /* Edited By Developer */
//#define _INT0               /*Comment it if not needed*/
//#define _INT1             /*Comment it if not needed*/
#define _INT2             /*Comment it if not needed*/
/*****************************************************************************/


/** Used Directories *********************************************************/
#include "datatypes.h"
#include "macros.h"
#include "registers.h"
#include <avr/interrupt.h>  //Mandatory to be able to use ISR routine format
/*****************************************************************************/


/** Function Prototypes ******************************************************/
#ifdef _INT0
    
    /*** Description:-
     * Function To enable EXT Interrupt 0, Fu Args: "sense_control"
     * sense_control Values = LOW_LOGIC /  LOGIC_CHANGE / FALLING_EDGE / RISING_EDGE */
    void __INT0_init(uint8 sense_control);
    
    /*** Description:-
     * Function used to set the Global Pointer called by ISR,
     * with the Developer created function */
    void __INT0_setISRCallBackFuncPointer(void (*ptr_to_func)(void));

#endif

#ifdef _INT1
    
    /*** Description:-
     * Function To enable EXT Interrupt 0, Fu Args: "sense_control"
     * sense_control Values = LOW_LOGIC /  LOGIC_CHANGE / FALLING_EDGE / RISING_EDGE */
    void __INT1_init(uint8 sense_control);

    /*** Description:-
     * Function used to set the Global Pointer called by ISR,
     * with the Developer created function */
    void __INT1_setISRCallBackFuncPointer(void (*ptr_to_func)(void));

#endif

#ifdef _INT2

    /*** Description:-
     * Function To enable EXT Interrupt 0, Fu Args: "sense_control"
     * sense_control Values = LOW_LOGIC /  LOGIC_CHANGE / FALLING_EDGE / RISING_EDGE */
    void __INT2_init(uint8 sense_control);

    /*** Description:-
     * Function used to set the Global Pointer called by ISR,
     * with the Developer created function */
    void __INT2_setISRCallBackFuncPointer(void (*ptr_to_func)(void));
#endif
/*****************************************************************************/

#endif /* EXTERNAL_INTERRUPT_H_ */
