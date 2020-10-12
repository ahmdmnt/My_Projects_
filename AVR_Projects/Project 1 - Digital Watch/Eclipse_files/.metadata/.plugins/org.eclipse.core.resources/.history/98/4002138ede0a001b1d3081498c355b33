/*****************************************************************************
 * external_interrupt.c
 * 
 *		**External Interrupt - Driver**
 *      Designed for AVR ATmega16 Microcontroller
 *
 *  Created on: Sep 6, 2020
 *      Author: Ahmed Montasser
 *****************************************************************************/

/** Used Directives **********************************************************/
#include "external_interrupt.h"
/*****************************************************************************/


/** Variable Definitions *****************************************************/
/*Define Global Pointer that will store the users ISR function call code*/
#ifdef _INT0
    static volatile void  (*g_INT0_callBack_ptr)(void);       //Function should be static volatile but when i did so it prompt a warning
#endif

#ifdef _INT1
    static volatile void  (*g_INT1_callBack_ptr)(void);
#endif

#ifdef _INT2
    static volatile void  (*g_INT2_callBack_ptr)(void);
#endif
/*****************************************************************************/


/** Functions Definitions ****************************************************/
#ifdef _INT0

    /*** ISR Description:-
     * ISR Call the global pointer to function to execute desired code */
    ISR(INT0_vect)
    {
        (*g_INT0_callBack_ptr)();
    }

    /*** Description:-
     * Function used to set the Global Pointer called by ISR,
     * with the Developer created function */
    void __INT0_setISRCallBackFuncPointer(void (*ptr_to_func)(void))
    {
        g_INT0_callBack_ptr = ptr_to_func;
    }

    /*** Description:-
     * Function To enable EXT Interrupt 0, Fu Args: "sense_control"
     * sense_control Values = LOW_LOGIC /  LOGIC_CHANGE / FALLING_EDGE / RISING_EDGE
     * pullupResistor = EN_PULLUP / DIS_PULLUP */
    void __INT0_init(uint8 sense_control, uint8 pullupResistor)
    {
        /*Disable Global Interrupt Flag; Critical Section*/
        DIS_GLOBAL_INTERRUPT;
        /*Configure INT0/PD2 as input pin*/
        DDRD  &= (~(1<<PD2));
        if(pullupResistor)
        {
        	PORTD |= (1<<PD2);
        }
        /*Enable (INT0) Module Interrupt flag*/
        GICR |= (1<<INT0);
        /*write ISC00 and ISC01 bits according to sense control value*/
        switch(sense_control)
        {
            case LOW_LOGIC:
                MCUCR &= (~(1<<ISC00)) & (~(1<<ISC01));
            break;

            case LOGIC_CHANGE:
                MCUCR |= (1<<ISC00);
                MCUCR &= (~(1<<ISC01));
            break;

            case FALLING_EDGE:
                MCUCR &= (~(1<<ISC00));
                MCUCR |= (1<<ISC01);
            break;

            case RISING_EDGE:
                MCUCR |= (1<<ISC00) & (1<<ISC01);
            break;

            default:break;
        }
        /*Enable Global Interrupt Flag back*/
        EN_GLOBAL_INTERRUPT;
    }
#endif

#ifdef _INT1

    /*** ISR Description:-
     * ISR Call the global pointer to function to execute desired code */
    ISR(INT1_vect)
    {
        (*g_INT1_callBack_ptr)();
    }

    /*** Description:-
     * Function used to set the Global Pointer called by ISR,
     * with the Developer created function */
    void __INT1_setISRCallBackFuncPointer(void (*ptr_to_func)(void))
    {
        g_INT1_callBack_ptr = ptr_to_func;
    }

    /*** Description:-
     * Function To enable EXT Interrupt 0, Fu Args: "sense_control"
     * sense_control Values = LOW_LOGIC /  LOGIC_CHANGE / FALLING_EDGE / RISING_EDGE
     * pullupResistor = EN_PULLUP / DIS_PULLUP */
    void __INT1_init(uint8 sense_control, uint8 pullupResistor)
    {
        /*Disable Global Interrupt Flag; Critical Section*/
        DIS_GLOBAL_INTERRUPT;
        /*Configure INT1/PD3 as input pin*/
        DDRD  &= (~(1<<PD3));
        if(pullupResistor)
        {
        	PORTD |= (1<<PD3);
        }
        /*write ISC10 and ISC11 bits according to sense control value*/
        switch(sense_control)
        {
            case LOW_LOGIC:
                MCUCR &= (~(1<<ISC10)) & (~(1<<ISC11));
            break;

            case LOGIC_CHANGE:
                MCUCR |= (1<<ISC10);
                MCUCR &= (~(1<<ISC11));
            break;

            case FALLING_EDGE:
                MCUCR &= (~(1<<ISC10));
                MCUCR |= (1<<ISC11);
            break;

            case RISING_EDGE:
                MCUCR |= (1<<ISC10) & (1<<ISC11);
            break;

            default:break;
        }
        /*Enable (INT1) Module Interrupt flag*/
        GICR |= (1<<INT1);
        /*Enable Global Interrupt Flag back*/
        EN_GLOBAL_INTERRUPT;
    }
#endif

#ifdef _INT2

    /*** ISR Description:-
     * ISR Call the global pointer to function to execute desired code */
    ISR(INT2_vect)
    {
        (*g_INT2_callBack_ptr)();
    }

    /*** Description:-
     * Function used to set the Global Pointer called by ISR,
     * with the Developer created function */
    void __INT2_setISRCallBackFuncPointer(void (*ptr_to_func)(void), uint8 pullupResistor)
    {
        g_INT2_callBack_ptr = ptr_to_func;
    }

    /*** Description:-
     * Function To enable EXT Interrupt 0, Fu Args: "sense_control"
     * sense_control Values = LOW_LOGIC /  LOGIC_CHANGE / FALLING_EDGE / RISING_EDGE
     * pullupResistor = EN_PULLUP / DIS_PULLUP */
    void __INT2_init(uint8 sense_control)
    {
        /*Disable Global Interrupt Flag; Critical Section*/
        DIS_GLOBAL_INTERRUPT;
        /*Configure INT2/PB2 as input pin*/
        DDRB  &= (~(1<<PB2));
        if(pullupResistor)
        {
        	PORTB |= (1<<PB2);
        }
        /*write ISC2 bits according to sense control value*/
        switch(sense_control)
        {
            case FALLING_EDGE:
                MCUCSR &= (~(1<<ISC2));
            break;

            case RISING_EDGE:
                MCUCSR |= (1<<ISC2);
            break;

            default:break;
        }
        /*Enable (INT2) Module Interrupt flag*/
        GICR |= (1<<INT2);
        /*Enable Global Interrupt Flag back*/
        EN_GLOBAL_INTERRUPT;
    }
#endif
/*****************************************************************************/
