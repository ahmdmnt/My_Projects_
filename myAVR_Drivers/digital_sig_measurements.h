/*******************************************************************************
 * digital_sig_measurements.h
 *
 *  Created on: Oct 13, 2020
 *      Author: Ahmed Montasser
 *******************************************************************************/

#ifndef DIGITAL_SIG_MEASUREMENTS_H_
#define DIGITAL_SIG_MEASUREMENTS_H_


/** Used Directives ************************************************************/
#include "datatypes.h"
/*******************************************************************************/


/** Function Definitions ********************************************************/

/*** Description:-
 *
 */
uint8 _SIG_getSignalDutyCycle(void);


/*** Description:-
 *  Function calculate the input signal period in uSeconds, through ICU Module.
 */
uint32 _SIG_getSignalPeriod_uS(void);

/*** Description:-
 *  Function calculate the input signal Frequency in Hertz, through ICU Module.
 */
float32 _SIG_getSignalFrequency_Hz(void);

/*******************************************************************************/

#endif /* DIGITAL_SIG_MEASUREMENTS_H_ */
