/*
 * dc_motor_pwm.h
 *
 *  Created on: Sep 23, 2020
 *      Author: montasse
 */


#ifndef MOTOR_DC_
#define MOTOR_DC_

/** Include Directives *******************************************************/
#include "PWM.h"
#include "DIO.h"
/** Macros Definitions *******************************************************/
#define FORWARD_DIR		0
#define BACKWARD_DIR	1
/** Static Configurations >>Edited By Developer<< ****************************/
#define MOTOR_IN1		PB5
#define MOTOR_IN2		PB4
#define MOTOR_PORT_DDR	DDR_B
#define MOTOR_PORT_PORT	PORT_B
/*****************************************************************************/


/** Variable Declaration *****************************************************/
typedef struct
{
	uint8 speed;		// Values from 0...100
	uint8 direction;	// FORWARD_DIR, FORWARD_DIR
}MOTOR_config;
/*****************************************************************************/


/** Function Declaration *****************************************************/
/* Description:-
 * Function used to start operating the MOTOR.
 */
void _DCMOTOR_motorOn(volatile const MOTOR_config *m_config_ptr);
/* Description:-
 * Function used to stop operating the MOTOR.
 */
void _DCMOTOR_motorOff(void);
/*****************************************************************************/
#endif	/*MOTOR_DC_*/
