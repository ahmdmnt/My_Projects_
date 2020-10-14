/*******************************************************************************
 * digital_sig_measurements.c
 *
 *  Created on: Oct 13, 2020
 *      Author: Ahmed Montasser
 *******************************************************************************/


/** Used Directives ************************************************************/
#include "digital_sig_measurements.h"
#include "ICU.h"
/*******************************************************************************/


/* Static Configuration ********************************************************/
#define ICU_CLK_PRESCALER   ICU_F_CPU_8     // Values: ICU_F_CPU, ICU_F_CPU_8, ICU_F_CPU_64, ICU_F_CPU_256, ICU_F_CPU_1024 
#define ICU_PRESCALER       8               // Values: 1, 8, 64, 256, 1024
#define MCU_FREQUENCY       1               // Values: 1, 8     <---(1MHz), (8MHz)
/*******************************************************************************/


/* Global Variable *************************************************************/
static uint8 edge_counter = 0;
/*******************************************************************************/



/* Function Prototype **********************************************************/
void _SIG_edgeProcessing_callBackFuncISR(void);
/*******************************************************************************/



/** Function Definitions ********************************************************/

/*** Description:-
 *  Function calculate the input signal (at: ICP1/PD6 pin) duty cycle, through ICU Module.
 */
uint8 _SIG_getSignalDutyCycle(void)
{
    uint16 t0_t_high;
    uint16 t1_t_period;
    uint16 t2_t_period_high;
    uint8  duty_cycle;

    /* Module Configs */
    ICU_config icu_configs = {RISING_EDGE, ICU_CLK_PRESCALER};

    /* Set the Call back function pointer in the ICU driver */
    __ICU_setCallBackFunctionGlobalPtr(_SIG_edgeProcessing_callBackFuncISR);

    /* Start the Module and find first rising edge*/
    __ICU_init(&icu_configs);

    /* Stop here till interrupt inc edge_counter value */
    while( edge_counter==0 );

    /*----------------------------------------------------*/
    if( edge_counter==1 )
    {
        /* Clear timer register */
        __ICU_clearTimerValue();

        /* Adjust the edge detection to falling edge */
        __ICU_setCaptureDetectionEdge(FALLING_EDGE);
    }
    /* Stop here till interrupt inc edge_counter value */
    while( edge_counter==1 );

    /*----------------------------------------------------*/
    if( edge_counter==2 )
    {
        /* fetch t_high time*/
        t0_t_high = __ICU_getInputCaptureTime();
        
        /* Adjust the edge detection to rising edge */
        __ICU_setCaptureDetectionEdge(RISING_EDGE);
    }
    /* Stop here till interrupt inc edge_counter value */
    while( edge_counter==2 );

    /*----------------------------------------------------*/
    if( edge_counter==3 )
    {
        /* fetch t_period time*/
        t1_t_period = __ICU_getInputCaptureTime();
        
        /* Adjust the edge detection to rising edge */
        __ICU_setCaptureDetectionEdge(FALLING_EDGE);  
    }
    /* Stop here till interrupt inc edge_counter value */
    while( edge_counter==3 );

    /*----------------------------------------------------*/
    if( edge_counter==4 )
    {
        /* fetch t_period+high time*/
        t2_t_period_high = __ICU_getInputCaptureTime();
        
        /* Stop the Module by function End */
        __ICU_deinit();        
    }

    /* Clear edge interrupt flag */
    edge_counter = 0;

    /* Calculate the Signal Duty Cycle */
    duty_cycle = (uint8)(((float)(t2_t_period_high - t1_t_period)/(t2_t_period_high - t0_t_high))*100);

    return duty_cycle;
}
/*******************************************************************************/

/*** Description:-
 *  Function calculate the input signal period in uSeconds, through ICU Module.
 */
uint32 _SIG_getSignalPeriod_uS(void)
{
    uint16 t0_t_high;
    uint16 t1_t_period_high;
    uint32  sig_period;

    /* Module Configs */
    ICU_config icu_configs = {RISING_EDGE, ICU_CLK_PRESCALER};

    /* Set the Call back function pointer in the ICU driver */
    __ICU_setCallBackFunctionGlobalPtr(_SIG_edgeProcessing_callBackFuncISR);

    /* Start the Module and find first rising edge*/
    __ICU_init(&icu_configs);


    /* Stop here till interrupt inc edge_counter value */
    while( edge_counter==0 );

    /*----------------------------------------------------*/
    if( edge_counter==1 )
    {
        /* Clear timer register */
        __ICU_clearTimerValue();

        /* Adjust the edge detection to falling edge */
        __ICU_setCaptureDetectionEdge(FALLING_EDGE);
    }
    /* Stop here till interrupt inc edge_counter value */
    while( edge_counter==1 );

    /*----------------------------------------------------*/
    if( edge_counter==2 )
    {
        /* fetch t_high time*/
        t0_t_high = __ICU_getInputCaptureTime();
    }
    /* Stop here till interrupt inc edge_counter value */
    while( edge_counter==2 );

    /*----------------------------------------------------*/
    if( edge_counter==3 )
    {
        /* fetch t_period time*/
        t1_t_period_high = __ICU_getInputCaptureTime();
        
        /* Stop the Module by function End */
        __ICU_deinit();  
    }

    /*Clear edge interrupt flag*/
    edge_counter = 0;

    /* Calculate the Signal Period */
    sig_period = (t1_t_period_high - t0_t_high);//*ICU_PRESCALER/MCU_FREQUENCY;
    sig_period *= (ICU_PRESCALER/MCU_FREQUENCY);

    return sig_period;
}
/*******************************************************************************/

/*** Description:-
 *  Function calculate the input signal Frequency in Hertz, through ICU Module.
 */
float32 _SIG_getSignalFrequency_Hz(void)
{
	uint32 sig_period;
	float32 sig_frequency;


	/* Get Signal period in micro seconds */
	sig_period = _SIG_getSignalPeriod_uS();

	/* convert period from micro to seconds and inverse the period value 1/time */
	sig_frequency = (float32)1000000/sig_period;

	return sig_frequency;
}
/*******************************************************************************/

void _SIG_edgeProcessing_callBackFuncISR(void)
{
    edge_counter++;
}
/*******************************************************************************/
