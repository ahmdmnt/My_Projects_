/*
 * dc_motor.c
 *
 *  Created on: Oct 2, 2020
 *      Author: montasse
 */

#ifndef DC_MOTOR_C_
#define DC_MOTOR_C_

#include "DIO.h"
#include "datatypes.h"
#include "registers.h"
#include "dc_motor.h"

void _MOTORDC_init(void)
{
	__DIO_setPinDirection(MOTOR_DDR, MOTOR_PIN1, OUTPUT_PIN);
	__DIO_setPinDirection(MOTOR_DDR, MOTOR_PIN2, OUTPUT_PIN);

	__DIO_writeOutputPinValue(MOTOR_PORT, MOTOR_PIN1, LOW);
	__DIO_writeOutputPinValue(MOTOR_PORT, MOTOR_PIN2, LOW);
}

void _MOTORDC_rotate(uint8 motor_state)
{
	switch(motor_state)
	{
	case OFF:
		__DIO_writeOutputPinValue(MOTOR_PORT, MOTOR_PIN1, LOW);
		__DIO_writeOutputPinValue(MOTOR_PORT, MOTOR_PIN2, LOW);
		break;
	case CW:
		__DIO_writeOutputPinValue(MOTOR_PORT, MOTOR_PIN1, HIGH);
		__DIO_writeOutputPinValue(MOTOR_PORT, MOTOR_PIN2, LOW);
		break;
	case CCW:
		__DIO_writeOutputPinValue(MOTOR_PORT, MOTOR_PIN1, LOW);
		__DIO_writeOutputPinValue(MOTOR_PORT, MOTOR_PIN2, HIGH);
		break;
	}
}


#endif /* DC_MOTOR_C_ */
