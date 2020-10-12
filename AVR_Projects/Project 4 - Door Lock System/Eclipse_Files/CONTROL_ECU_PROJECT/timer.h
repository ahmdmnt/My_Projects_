/***********************************************************************************************
 * timer.h
 * 
 *		**Timer - Driver**
 *      This Module is Designed to activate the Timers.
 *          - Timer0 > 8 bits.
 *          - Timer1 > 16 bits.
 *          - Timer2 > 8 bits.
 *      Designed for AVR ATmega16 Microcontroller
 *
 *  Created on: Sep 6, 2020
 *      Author: Ahmed Montasser
 ***********************************************************************************************
 * > When Using this Module :-
 * -----------------------------
 * 1. Define the needed interrupt to allow its code, otherwise it will be disbaled:
 *      #define _TIMER0
 *      #define _TIMER1
 *      #define _TIMER2
 * 
 * 2. Define the OCx Pin Status if needed to be Enabled [TRUE or FALSE]:
 *      #define TIMER0_ENABLE_OC0_PIN TRUE
 *      #define TIMER1_ENABLE_OC0_PIN TRUE
 *      #define TIMER2_ENABLE_OC0_PIN TRUE
 * 
 * 3. Write the Desired ISR Code in a C created Function of your own, in the following format:
 *      void FUNCTION_NAME(void)
 *          { ...Function Code ... }
 * 
 * 4. Send the created function name to the driver via:
 *      __TIMERx_CTC_setISRCallBackFuncPointer(<FUNCTION_NAME>);           (where X= 0, 1, 2)
 * 
 * 5. Check the of end file; "Note" section;
 *          describes the timer intervals according to Clock Prescaler
 * 
 * 6. Set the Timer Clock Prescaler with Below Inputs only:
 *      - CLK_NO_PRESCALER      - CLK_PRESCALER_8
 *      - CLK_PRESCALER_64      - CLK_PRESCALER_256
 *      - CLK_PRESCALER_1024
 * 
 * 7. Set the Timer Clock Prescaler with Below Inputs only:
 *      - TOGGLE_OCx_PIN      - CLEAR_OCx_PIN
 *      - SET_OCx_PIN
 * 
 * 8. Timer1 is working with one channel only [A] and compare register is OCR1A.
 * 
 **********************************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

/** Used Directories *********************************************************/
#include "datatypes.h"
#include "macros.h"
#include "registers.h"
/*****************************************************************************/


/** Configuration Parameters ***************************************************/
/*** Defined Symbolic Constants ******/
#define TIMER0                  0
#define TIMER1                  1
#define TIMER2                  2

#define NON_PWM_MODE            1
#define ENABLED                 1
#define DISABLED                0

#define OCx_DISABLED            0
#define TOGGLE_OCx_PIN          1    
#define CLEAR_OCx_PIN           2    
#define SET_OCx_PIN             3
/*****************************************************************************/


/*** Static Configurations ******/     /** Edited By Developer **/
#define TIMER_OCx_PIN DISABLED         /*ENABLED _OR_ DISABLED*/
/*****************************************************************************/


/** Variables Declaration ****************************************************/
typedef enum
{
    TIMER_NO_CLK, TIMER_F_CPU, TIMER_F_CPU_8, TIMER_F_CPU_64, TIMER_F_CPU_256, TIMER_F_CPU_1024
}t_clock;

typedef struct
{
    uint8   timer_module;       //values : TIMER0 / TIMER1 / TIMER2 
	t_clock timer_clock;        //values: NO_CLK,F_CPU_CLK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
	uint16  compare_value;      //values: from 0 ... 65535
    uint8   OCx_mode;           //values: OCx_DISABLED / TOGGLE_OCx_PIN / CLEAR_OCx_PIN / SET_OCx_PIN
}configType_TIMER;
/*****************************************************************************/

/** Function Prototypes ******************************************************/

#if(TIMER_OCx_PIN == DISABLED)
    
    /*** Description:-
     * Used to Set the Global Pointer with desired function which will be called by ISR 
     * Func Arg: Pass the desired function Name */
    void __TIMER_CTC_setISRCallBackFuncPointer(uint8 timer_module, void (*ptr_to_func)(void));

#endif

/*** Description:-
 * Used to Start the Timer with the desired Configuration
 * Func Args, struct Members: timer_clock / compare_value / OC0_mode */
void __TIMER_CTC_startTimer(const configType_TIMER *t_configPointer);
        
/*** Description:-
 * Used to Disable the timer */
void __TIMER_CTC_stopTimer(uint8 timer_module);


/**********************************************************************************************/ 
/* - Notes:-
 * -----------
 ** For Timer 0 [8 Bits: 0...255] - CPU Clock: 1MHz:
 *  - No   Prescaler : (from: 1   uS - to: 255  uS )
 *  - 8    Prescaler : (from: 8   uS - to: 2    mS )
 *  - 64   Prescaler : (from: 64  uS - to: 0.01  S )
 *  - 256  Prescaler : (from: 255 uS - to: 0.06  S )
 *  - 1024 Prescaler : (from: 1   mS - to: 0.26  S )
 ********************************************************
 ** For Timer 0 [8 Bits: 0...255] - CPU Clock: 8MHz:
 *  - No   Prescaler : (from:  - to: )
 *  - 8    Prescaler : (from:  - to: )
 *  - 64   Prescaler : (from:  - to: )
 *  - 256  Prescaler : (from:  - to: )
 *  - 1024 Prescaler : (from:  - to: )
 **********************************************************************************************
 ** For Timer 1 [16 Bits: 0...65535] - CPU Clock: 1MHz:
 *  - No   Prescaler : (from: 1   uS - to: 0.065 S )
 *  - 8    Prescaler : (from: 8   uS - to: 0.52  S )
 *  - 64   Prescaler : (from: 64  uS - to: 4.19  S )
 *  - 256  Prescaler : (from: 256 uS - to: 16.7  S )
 *  - 1024 Prescaler : (from: 1   mS - to: 67    S )
 ********************************************************
 ** For Timer 1 [16 Bits: 0...65535] - CPU Clock: 8MHz:
 *  - No   Prescaler : (from: 0.125 uS - to: )
 *  - 8    Prescaler : (from: 1     uS - to: )
 *  - 64   Prescaler : (from: 8     uS - to: 0.52 S)
 *  - 256  Prescaler : (from: 32    uS - to: 2.08 S)
 *  - 1024 Prescaler : (from: 0.125 mS - to: 8.37 S)
 **********************************************************************************************/
#endif /* TIMER_H_ */
