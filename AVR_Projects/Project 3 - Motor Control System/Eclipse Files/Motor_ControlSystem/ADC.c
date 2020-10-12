/**********************************************************************************************
 * ADC.c
 * 
 *		**ADC - Driver**
 *      Designed for AVR ATmega16 Microcontroller
 *
 *  Created on: Sep 6, 2020
 *      Author: Ahmed Montasser
 ***********************************************************************************************/

/** Used Directives **********************************************************/
#include "ADC.h"
/*****************************************************************************/


/** Variable Definitions *****************************************************/
#ifdef ISR_BASED
    /* Global Variable To save ADC fetched value, volatile used by ISR */
    volatile uint16 g_adc_value;
#endif
/*****************************************************************************/


/** Functions Definitions ****************************************************/

/*** Description:-
 * ADC_init function to Enable ADC Module, Fu Args: "enum clock_prescaler" 
 * clock_prescaler values = NO_CLK, F_CPU, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024 */
void   __ADC_init(clock_ADC clock_prescaler)
{
    /*Set the Reference Selection Value according to given config*/
    ADMUX = (ADMUX&0b00111111) | (REF_SELECTION<<6);
    
    /*Set ADLAR Value according to Resolution Configuration*/
    #if(ADC_RESOLUTION == _10_BITS)
        CLR_BIT(ADMUX, ADLAR);
    #elif(ADC_RESOLUTION == _8_BITS)
        SET_BIT(ADMUX, ADLAR); //If *bits neglect the LSB bits
    #endif

    /*Enable/Disable Interrupt according to Static configs*/
    #ifdef POLLING_BASED
        CLR_BIT(ADCSRA, ADIE);
    #endif
    #ifdef ISR_BASED
        SET_BIT(ADCSRA, ADIE);
        EN_GLOBAL_INTERRUPT;
    #endif
    
    /*Enable the ADC Module*/
    SET_BIT(ADCSRA, ADEN);
    
    /*Set the ADC Prescaler=8 Fadc = 125KHz*/
    ADCSRA = (ADCSRA&0b11111000) | (clock_prescaler);
}

#ifdef POLLING_BASED

    #if(ADC_RESOLUTION == _10_BITS)

        /*** Description:-
        * Read the ADC Channel Analogue Value, Fu Args: "channel_number" 
        * channel_number values = ADC0, ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7 */
        uint16 __ADC_PB_readChannel_10bits(channel_ADC channel_number)
        {
            /*Set the desired ADC Channel*/
            ADMUX = (ADMUX & 0b11100000) | (channel_number & 0b00000111);
            /*ADC Start Conversion*/
            SET_BIT(ADCSRA,ADSC);
            /*Wait until ADC Module Execution done and Flag is raised*/
            while( READ_BIT(ADCSRA,ADIF)==LOW );
            /*Clear the Raised flag*/
            SET_BIT(ADCSRA,ADIF);

            /*Return the fetched Value value saved in first 10 bits*/
            return ADC;
        }

    #elif(ADC_RESOLUTION == _8_BITS)

        /*** Description:-
        * Read the ADC Channel Analogue Value, Fu Args: "channel_number" 
        * channel_number values = ADC0, ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7 */
        uint8  __ADC_PB_readChannel_8bits(channel_ADC channel_number)
        {
            /*Set the desired ADC Channel*/
            ADMUX = (ADMUX & 0b11100000) | (channel_number & 0b00011111);
            /*ADC Start Conversion*/
            SET_BIT(ADCSRA,ADSC);
            /*Wait until ADC Module Execution done and Flag is raised*/
            while( READ_BIT(ADCSRA,ADIF)==LOW );
            /*Clear the Raised flag*/
            SET_BIT(ADCSRA,ADIF);

            /*Return the fetched Value*/
            return ADCH; 
        }

    #endif

#endif

#ifdef ISR_BASED

    #if(ADC_RESOLUTION == _10_BITS)

        /*** Description:-
        * Read the ADC Channel Analogue Value, Fu Args: "channel_number" 
        * channel_number values = ADC0, ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7 */
        void __ADC_IB_readChannel_10bits(channel_ADC channel_number) //Async Function
        {
            /*Set the desired ADC Channel*/
            ADMUX = (ADMUX & 0b11100000) | (channel_number & 0b00011111);
            /*ADC Start Conversion*/
            SET_BIT(ADCSRA,ADSC);
        }

    #elif(ADC_RESOLUTION == _8_BITS)

        /*** Description:-
        * Read the ADC Channel Analogue Value, Fu Args: "channel_number" 
        * channel_number values = ADC0, ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7 */
        void __ADC_IB_readChannel_8bits(channel_ADC channel_number)
        {
            /*Set the desired ADC Channel*/
            ADMUX = (ADMUX & 0b11100000) | (channel_number & 0b00011111);
            /*ADC Start Conversion*/
            SET_BIT(ADCSRA,ADSC);
        }

    #endif

    /*** ISR Description:-
     * Fetch the ADC Value from ADC Register to Global Variable */
    ISR(ADC_vect)
    {
        #if(ADC_RESOLUTION == _10_BITS)
            g_adc_value = ADC;
        #elif(ADC_RESOLUTION == _8_BITS)
            g_adc_value = ADCH;
        #endif
    }

#endif
/*****************************************************************************/
