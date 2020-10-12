/**********************************************************************************************
 * ADC.h
 * 
 *		**ADC - Driver**
 *      Designed for AVR ATmega16 Microcontroller
 *
 *  Created on: Sep 6, 2020
 *      Author: Ahmed Montasser
 **********************************************************************************************
 * > When Using this Module :-
 * -----------------------------
 * 1. Edit Configuration Parameters as desired.
 * 
 * 2. UF ISR Based, adc value will be extracted in externed global variable "g_adc_value"
 * 
 **********************************************************************************************/

#ifndef ADC_H_
#define ADC_H_

/** Configuration Parameters ***************************************************/
/*** Defined Symbolic Constants ******/
#define AREF        0
#define VCC         1
#define INT_2_56V   3
#define _10_BITS    10
#define _8_BITS     8
/*** Static Configurations ******/     /* Edited By Developer */
//#define ISR_BASED                      /*Comment it if not needed*/
#define POLLING_BASED                  /*Comment it if not needed*/
#define ADC_RESOLUTION  _8_BITS       /* Values = 10 (or) 8 */
#define REF_SELECTION   VCC
/*****************************************************************************/

/** Used Directives **********************************************************/
#include "datatypes.h"
#include "macros.h"
#include "registers.h"
#include <avr/interrupt.h>
/*****************************************************************************/

/** Externed Global Variables ************************************************/
#ifdef ISR_BASED
	extern g_adc_value;
#endif
/*****************************************************************************/

/** Variables Declaration ****************************************************/
typedef enum
{NO_CLK, ADC_F_CPU_2, ADC_F_CPU_4, ADC_F_CPU_8, ADC_F_CPU_16, ADC_F_CPU_32, ADC_F_CPU_64, ADC_F_CPU_128}clock_ADC;

typedef enum
{ADC0, ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7}channel_ADC;
/*****************************************************************************/

/** Function Prototypes ******************************************************/

/*** Description:-
 * ADC_init function to Enable ADC Module, Fu Args: "enum clock_prescaler" 
 * clock_prescaler values = ADC_F_CPU_2, ADC_F_CPU_2, ADC_F_CPU_2, ADC_F_CPU_8, ADC_F_CPU_16, ADC_F_CPU_32, ADC_F_CPU_64, ADC_F_CPU_128 */
void   __ADC_init(uint8 clock_prescaler);

#ifdef POLLING_BASED
    #if(ADC_RESOLUTION == 10)

        /*** Description:-
        * Read the ADC Channel Analogue Value, Fu Args: "channel_number" 
        * channel_number values = ADC0, ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7 */
        uint16 __ADC_PB_readChannel_10bits(uint8 channel_number);

    #elif(ADC_RESOLUTION == 8)

        /*** Description:-
        * Read the ADC Channel Analogue Value, Fu Args: "channel_number" 
        * channel_number values = ADC0, ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7 */
        uint8  __ADC_PB_readChannel_8bits(channel_ADC channel_number);
    
    #endif
#endif

#ifdef ISR_BASED
    #if(ADC_RESOLUTION == 10)
        
        /*** Description:-
        * Read the ADC Channel Analogue Value, Fu Args: "channel_number" 
        * channel_number values = ADC0, ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7 */
        void __ADC_IB_readChannel_10bits(channel_ADC channel_number);
    
    #elif(ADC_RESOLUTION == 8)
    
        /*** Description:-
        * Read the ADC Channel Analogue Value, Fu Args: "channel_number" 
        * channel_number values = ADC0, ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7 */
        void __ADC_IB_readChannel_8bits(channel_ADC channel_number);
    
    #endif
#endif
/*****************************************************************************/

#endif /* ADC_H_ */
