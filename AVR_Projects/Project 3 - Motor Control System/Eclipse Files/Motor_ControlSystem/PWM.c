/*****************************************************************************
 * PWM.c
 * 
 *		**PWM - Driver**
 *      Designed for AVR ATmega16 Microcontroller
 *
 *  Created on: Sep 6, 2020
 *      Author: Ahmed Montasser
 *****************************************************************************/

/** Used Directives **********************************************************/
#include "PWM.h"
/*****************************************************************************/

/** Functions Definitions ****************************************************/
#ifdef _PWM0

    /*** Description:-
     * Used to Start the PWM with the desired Configuration
     * Func Args, struct Members: PWM_clock / compare_value / OC0_mode */
    void __PWM0_startModule(const configType_PWM0 *pwm0_configPointer)
    {
        /*Disable Global Interrupt flag; Entering Critical Section*/
        DIS_GLOBAL_INTERRUPT;
        /*Initialize the TCNT0 with 0 Value*/
        TCNT0 = 0x00;
        /*Set Compare Register with compare value*/
        OCR0 = pwm0_configPointer->duty_cycle;
        /*Set PB3/OC0 as Output Pin*/
        SET_BIT(DDRB, PB3);
        /*Set Module in PWM Mode*/
        CLR_BIT(TCCR0, FOC0);
        /*Set The PWM in Fast PWM Mode: WGM00=1 / WGM01 = 1*/
        SET_BIT(TCCR0, WGM00);
        SET_BIT(TCCR0, WGM01);
        /*Disable Module Interrupt Enable flag*/
        CLR_BIT(TIMSK, OCIE0);
        /*Set Compare Output Mode, non-PWM Mode Pins*/
        TCCR0 = (TCCR0&0b11001111) | (pwm0_configPointer->PWM_mode<<4);
        /*Set the PWM Clock Prescaler*/
        TCCR0 = (TCCR0&0xF8) | (pwm0_configPointer->PWM_clock&0x07);
        /*Enable Global Interrupt flag; Exiting Critical Section*/
        EN_GLOBAL_INTERRUPT;
    }


    /*** Description:-
     * Used to Disable the PWM */
    void __PWM0_stopModule(void)
    {
        /*Disable Global Interrupt flag; Exiting Critical Section*/
        DIS_GLOBAL_INTERRUPT;
        /*Disable PWM Clock Source: will Disable the PWM itself*/
        TCCR0 = 0x00;
        /*Enable Global Interrupt flag; Exiting Critical Section*/
        EN_GLOBAL_INTERRUPT;
    }
#endif


#ifdef _PWM1

    /*** Description:-
     * Used to Start the PWM with the desired Configuration
     * Func Args, struct Members: PWM_clock / compare_value / OC0_mode */    
    void __PWM1_startModule(const configType_PWM1 *pwm1_configPointer)
    {
        /*Disable Global Interrupt flag; Entering Critical Section*/
        DIS_GLOBAL_INTERRUPT;
        /*Initialize the TCNT0 with 0 Value*/
        TCNT1 = 0x0000;
        /*Set ICR1 with TOP value for adjusting timer frequency*/
        ICR1 = pwm1_configPointer->top_prescale_value;
        /*Set Compare Register with compare value*/
        OCR1A = pwm1_configPointer->duty_cycle;
        /*Set PWM in Non PWM Mode*/
        CLR_BIT(TCCR1A, FOC1A);
        CLR_BIT(TCCR1A, FOC1B);
        /*Set Module with Fast PWM Mode (TOP = ICR1)*/
        CLR_BIT(TCCR1A, WGM10);
        SET_BIT(TCCR1A, WGM11);
        SET_BIT(TCCR1B, WGM12);
        SET_BIT(TCCR1B, WGM13);
        /*Disable Module Interrupt Enable Flag*/
        CLR_BIT(TIMSK, OCIE1A);
        /*Set PD5/OC1A as Output Pin*/
        SET_BIT(DDRD, PD5);
        /*Set Compare Output Mode [non-PWM Mode] Pins*/
        TCCR1A = (TCCR1A&0b00111111) | (pwm1_configPointer->PWM_mode<<6);
        /*Set the PWM Clock Prescaler*/
        TCCR1B = (TCCR1B&0xF8) | (pwm1_configPointer->PWM_clock&0x07);
        /*Enable Global Interrupt flag; Exiting Critical Section*/
        EN_GLOBAL_INTERRUPT;
    }


    /*** Description:-
     * Used to Disable the PWM */
    void __PWM1_stopModule(void)
    {
        /*Disable Global Interrupt flag; Entering Critical Section*/
        DIS_GLOBAL_INTERRUPT;
        /*Disable PWM Clock Source: will Disable the PWM itself*/
        TCCR1A = 0x00;
        TCCR1B = 0x00;
        /*Enable Global Interrupt flag; Exiting Critical Section*/
        EN_GLOBAL_INTERRUPT;
    }
#endif


#ifdef _PWM2
#endif