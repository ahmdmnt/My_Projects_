/*
 * alarm.c
 *
 *  Created on: Oct 2, 2020
 *      Author: montasse
 */

#ifndef ALARM_C_
#define ALARM_C_

#include "alarm.h"

void _ALARM_init(void)
{
	__DIO_setPinDirection(ALARM_DDR, ALARM_PIN, OUTPUT_PIN);

	__DIO_writeOutputPinValue(ALARM_PORT, ALARM_PIN, LOW);
}

void _ALARM_state(uint8 state)
{
	switch(state)
	{
	case OFF:
		__DIO_writeOutputPinValue(ALARM_PORT, ALARM_PIN, LOW);
		break;


	case ON:
		__DIO_writeOutputPinValue(ALARM_PORT, ALARM_PIN, HIGH);
		break;
	
    
    default:
		/*Do nothing*/
		break;
	}
}


#endif /* ALARM_C_ */
