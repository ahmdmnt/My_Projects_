/**********************************************************************************************
 * ICU.c
 * 
 *		**Input Capture Unit - Driver**
 *      Designed for AVR ATmega16 Microcontroller
 *
 *  Created on: Oct 13, 2020
 *      Author: Ahmed Montasser
 ***********************************************************************************************/

/** Used Directives **********************************************************/
#include "ICU.h"
#include <avr/interrupt.h>
/*****************************************************************************/


/** MACRO Definitions ********************************************************/
#define NULL_PTR        ((void*)0)
/*****************************************************************************/

/** Global Variables *********************************************************/
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
/*****************************************************************************/


/** Functions Definitions ****************************************************/

/*** Description:-
 * Function initialize the module
 * 	capture_edge : RISING_EDGE, FALLING_EDGE
 * 	clock :  ICU_NO_CLK, ICU_F_CPU, ICU_F_CPU_8, ICU_F_CPU_64, ICU_F_CPU_256, ICU_F_CPU_1024
 */
void __ICU_init(const ICU_config *configs_ptr)
{
    /* Module Configs:-
     * OCx Pins Disconnected: COM1A1/COM1B0 COM1A0/COM1B0 = ZERO
     * Non-PWM mode: FOC1A/FOC1B = ONE
     * TIMER Mode: (Normal) WGM13/WGM12/WGM11/WGM10 = ZERO
     * ICU Nosie Canceller (Disabled): ZERO
     * Clear TCNT1 Register
     * Clear ICR1 Register
     * Enable Module Interrupt Enable (TICIE1 = ONE)
     * Enable I-Bit, Global Interrupt
     * 
     * Set ICP1 (PD6) Pin as Input Pin
     * 
     * ICU Edge Select: USER_CONFIG
     * Clock Prescaler: USER_CONFIG
     */

    SET_BIT(TCCR1A, FOC1A);
    SET_BIT(TCCR1A, FOC1B);
    TCNT1 = 0;
    ICR1  = 0;
    SET_BIT(TIMSK, TICIE1);
    EN_GLOBAL_INTERRUPT;

    CLR_BIT(DDRD, PD6);

    TCCR1B = (TCCR1B & 0b10111111) | (configs_ptr->capture_edge<<6);
    TCCR1B = (TCCR1B & 0b11111000) | (configs_ptr->clock);
}


/*** Description:-
 *  Function to set the global pointer to function
 */
void __ICU_setCallBackFunctionGlobalPtr(void (*callBackPtr_ICU_ISR)(void))
{
    g_callBackPtr = callBackPtr_ICU_ISR;
}


/*** Description:-
 *  Function to adjust the detection of capture edge
 */
void __ICU_setCaptureDetectionEdge(const uint8 capture_edge)
{
    TCCR1B = (TCCR1B & 0b10111111) | (capture_edge<<6);
}


/*** Description:-
 *  Get the Time value of capture
 */
uint16 __ICU_getInputCaptureTime(void)
{
    return ICR1;
}


/*** Description:-
 *  Clear timer register, to count from beginning
 */
void  __ICU_clearTimerValue(void)
{
    TCNT1 = 0;
}

/*** Description:-
 *  De Init the Module
 */
void  __ICU_deinit(void)
{
    /*
     *  Clear all registers and module interrupt enable bit
     */ 
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 =  0;
    ICR1  =  0;

    CLR_BIT(TIMSK, TICIE1);
}

/*****************************************************************************/


/** Interrupt Service Routine ************************************************/
ISR(TIMER1_CAPT_vect)
{
    if(g_callBackPtr != NULL_PTR )
    {
        (*g_callBackPtr)();
    }
}
/*****************************************************************************/
