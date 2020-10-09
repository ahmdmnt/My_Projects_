/*
 * dc_motor.h
 *
 *  Created on: Oct 2, 2020
 *      Author: montasse
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#define OFF 0
#define CW	1
#define CCW 2

#define MOTOR_DDR	DDR_B
#define MOTOR_PORT	PORT_B
#define MOTOR_PIN1	PB6
#define MOTOR_PIN2	PB7

void _MOTORDC_init(void);

void _MOTORDC_rotate(uint8 motor_state);

#endif /* DC_MOTOR_H_ */
