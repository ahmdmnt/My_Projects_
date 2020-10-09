/*
 * alarm.h
 *
 *  Created on: Oct 2, 2020
 *      Author: montasse
 */

#ifndef ALARM_H_
#define ALARM_H_

#include "DIO.h"
#include "datatypes.h"
#include "registers.h"

#define OFF 0
#define ON	1

/** Static Configuration *Edited By Developer**********************/
#define ALARM_DDR	DDR_A
#define ALARM_PORT	PORT_A
#define ALARM_PIN	PA0
/******************************************************************/

void _ALARM_init(void);

void _ALARM_state(uint8 motor_state);

#endif /* ALARM_H_ */
