/*****************************************************************************
 * timer.c
 * 
 *		**Timer - Driver**
 *      Designed for AVR ATmega16 Microcontroller
 *
 *  Created on: Sep 6, 2020
 *      Author: Ahmed Montasser
 *****************************************************************************/


/** Used Directives **********************************************************/
#include "tim.h"
#if(TIMER_OCx_PIN == DISABLED)
    #include <avr/interrupt.h>  //Mandatory to be able to use ISR routine format
#endif
/*****************************************************************************/


/** Variable Definitions *****************************************************/
#if(TIMER_OCx_PIN == DISABLED)
    /*Define Global Pointer that will store the users ISR function call code*/
    static volatile void  (*g_TIMER0_callBack_ptr)(void);
    static volatile void  (*g_TIMER1_callBack_ptr)(void);
#endif
/*****************************************************************************/


/** Functions Definitions ****************************************************/

#if(TIMER_OCx_PIN == DISABLED)

    /*** ISR Description:-
     * When Interrupt occurs the Global pointer will call the user-defined function */
    ISR(TIMER0_COMP_vect)
    {
        (*g_TIMER0_callBack_ptr)();
    }

    /*** ISR Description:-
     * When Interrupt occurs the Global pointer will call the user-defined function */
    ISR(TIMER1_COMPA_vect)
    {
        (*g_TIMER1_callBack_ptr)();
    }


    /*** Description:-
     * Used to Set the Global Pointer with desired function which will be called by ISR 
     * Func Arg: Pass the desired function Name */
    void __TIMER_CTC_setISRCallBackFuncPointer(uint8 timer_module, void (*ptr_to_func)(void))
    {
        switch(timer_module)
        {
            case TIMER0:
                g_TIMER0_callBack_ptr = ptr_to_func;
            break;

            case TIMER1:
                g_TIMER1_callBack_ptr = ptr_to_func;
            break;

            case TIMER2:break;
            default:break;
        }
    }

#endif


/*** Description:-
 * Used to Start the Timer with the desired Configuration
 * Func Args, struct Members: timer_clock / compare_value / OC0_mode */
void __TIMER_CTC_startTimer(const configType_TIMER *t_configPointer)
{
    switch(t_configPointer->timer_module)
    {
        case TIMER0:
            /*Disable Global Interrupt flag; Entering Critical Section*/
             DIS_GLOBAL_INTERRUPT;
            /*Initialize the TCNT0 with 0 Value*/
            TCNT0 = 0x00;
            /*Set Compare Register with compare value*/
            OCR0 = t_configPointer->compare_value;
            /*Set Timer in Non PWM Mode*/
            SET_BIT(TCCR0, FOC0);
            /*Set The timer in CTC Mode: WGM00=0 / WGM01 = 1*/
            CLR_BIT(TCCR0, WGM00);
            SET_BIT(TCCR0, WGM01);
            /*Enable Module Timer 0 Interrupt flag; if OC0 Pin is Disabled*/
            #if(TIMER_OCx_PIN == DISABLED)
                SET_BIT(TIMSK, OCIE0);
            #elif(TIMER_OCx_PIN == ENABLED)
                /*Disable Interrupt Enable Module*/
                CLR_BIT(TIMSK, OCIE0);
                /*Set OC0 as Output Pin*/
                SET_BIT(DDRB, PB3);
            #endif
            /*Set Compare Output Mode, non-PWM Mode Pins*/
            TCCR0 = (TCCR0&0b11001111) | (t_configPointer->OCx_mode<<4);
            /*Set the Timer Clock Prescaler*/
            TCCR0 = (TCCR0&0xF8) | (t_configPointer->timer_clock&0x07);
            /*Enable Global Interrupt flag; Exiting Critical Section*/
            EN_GLOBAL_INTERRUPT;
        break;

        case TIMER1:
            /*Disable Global Interrupt flag; Entering Critical Section*/
            DIS_GLOBAL_INTERRUPT;
            /*Initialize the TCNT0 with 0 Value*/
            TCNT1 = 0x0000;
            /*Set Compare Register with compare value*/
            OCR1A = t_configPointer->compare_value;
            /*Set Timer in Non PWM Mode*/
            SET_BIT(TCCR1A, FOC1A);
            /*Set The timer in CTC Mode*/
            CLR_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
            /*Enable Module Timer 0 Interrupt flag; if OC0 Pin is Disabled*/
            #if(TIMER_OCx_PIN == DISABLED)
                /*Enable Interrupt Enable Module*/
                SET_BIT(TIMSK, OCIE1A);
            #elif(TIMER_OCx_PIN == ENABLED)
                /*Disable Interrupt Enable Module*/
                CLR_BIT(TIMSK, OCIE1A);
                /*Set OC0 as Output Pin*/
                SET_BIT(DDRD, PD5);
            #endif
            /*Set Compare Output Mode [non-PWM Mode] Pins*/
            TCCR1A = (TCCR1A&0b00111111) | (t_configPointer->OCx_mode<<6);
            /*Set the Timer Clock Prescaler*/
            TCCR1B = (TCCR1B&0xF8) | (t_configPointer->timer_clock&0x07);
            /*Enable Global Interrupt flag; Exiting Critical Section*/
            EN_GLOBAL_INTERRUPT;        
        break;

        case TIMER2:break;
        default:break;
    }



}


/*** Description:-
 * Used to Disable the timer */
void __TIMER_CTC_stopTimer(uint8 timer_module)
{
    switch(timer_module)
    {
        case TIMER0:
            /*Disable Global Interrupt flag; Exiting Critical Section*/
            DIS_GLOBAL_INTERRUPT;
            /*Disable Timer Clock Source: will Disable the Timer itself*/
            TCCR0 = 0x00;
            /*for double confirming disable module interrupt flag*/
            CLR_BIT(TIMSK, OCIE0);    //TIMSK &= ~(1<<OCIE0);
            /*Enable Global Interrupt flag; Exiting Critical Section*/
            EN_GLOBAL_INTERRUPT;
        break;

        case TIMER1:
            /*Disable Global Interrupt flag; Entering Critical Section*/
            DIS_GLOBAL_INTERRUPT;
            /*Disable Timer Clock Source: will Disable the Timer itself*/
            TCCR1A = 0x00;
            TCCR1B = 0x00;
            /*for double confirming disable module interrupt flag as well*/
            CLR_BIT(TIMSK, OCIE1A);
            /*Enable Global Interrupt flag; Exiting Critical Section*/
            EN_GLOBAL_INTERRUPT;
        break;

        case TIMER2:break;
        default:break;
    }
}
