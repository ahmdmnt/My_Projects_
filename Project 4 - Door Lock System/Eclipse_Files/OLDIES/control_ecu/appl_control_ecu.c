/***************************************************************************************************
 * appl_hmi_ecu.c
 * 		Application Software for System Control ECU (F_CPU = 8MHz).
 * 			- Saving and Checking Password Correctness for User Password over EEPROM.
 * 			- Open/Close Door through DC Motor.
 * 			- Initiate Alarm in case invalid Credentials Enter several times.
 * 			- Receive needed Data for Human Interface-ECU through UART
 *
 *  Created on: Sep 29, 2020
 *      Author: Ahmed Montasser
 **************************************************************************************************/

/* Preprocessor Section *****************************************/
#include "DIO.h"
#include "tim.h"
#include "UART.h"
#include "ext_eeprom.h"
#include "dc_motor.h"
#define FOREVER 1

#define ECU_ADDR	0x01
#define PASSWORD_MEM_ADDR_LOC	0x0F

#define ALARM_DDR	DDR_A
#define ALARM_PORT	PORT_A
#define ALARM_PIN	PA0

/* Table of defined Communication Messages between the two ECUs */
#define UART_READY	0xFF
//Received Messages from HMI-ECU:-
#define SETUP_NEW_PASSWORD		0x01
#define CHANGE_PASSWORD			0x02
#define CHECK_LOGIN_CREDENTIALS	0x03
#define OPEN_DOOR				0x04
#define CLOSE_DOOR				0x05
//Replies Sent to HMI-ECU:-
#define TASK_SUCCEED			0x11
#define PASSWORD_NOT_MATCHED	0x21
/****************************************************************/

uint8 systemPasswordTasks(uint8 task_type);
void TIMER1_ISR_function(void);

uint8 task_to_do;						//Message Task indetification
uint8 rx_passwords[16];		//UART Received Message Variable
uint8 user_authenticated_flag=FALSE;

int main(void)
{

	/*-------------------------------------------------------------------------*/
	uint8 result = 0x00;

	/*TIMER1 Configuration Parameters*/
	configType_TIMER timer1_configs = {TIMER1, TIMER_F_CPU_64, 65534, OCx_DISABLED};

	/*UART Configuration Parameters*/
	UART_config uart_configs = {9600, _8_BIT_DATA, ONE_STOP_BITS, DISABLE_PARITY};


	/*-------------------------------------------------------------------------*/
	/* Initialize the Motor Control Pins */
	_MOTORDC_init();

	/* Initialize the Alarm Control Pin */
	__DIO_setPinDirection(ALARM_DDR, ALARM_PIN, OUTPUT_PIN);
	__DIO_writeOutputPinValue(ALARM_PORT, ALARM_PIN, LOW);


	/* Initialize TIMER1 ISR CallBack Function */
	__TIMER_CTC_setISRCallBackFuncPointer(TIMER1, TIMER1_ISR_function); //__TIMER_CTC_startTimer(&timer1_configs);

	/* Initialize EEPROM */
	_EXT_EEPROM_init(ECU_ADDR);

	/* Initialize UART Module */
	__UART_init(&uart_configs);
	/*-------------------------------------------------------------------------*/


	while(FOREVER)
	{
		/*-------------------------------------------------------------------------*/
		__UART_sendByte(UART_READY);
		task_to_do = __UART_receiveByte();

		switch(task_to_do)
		{
		case SETUP_NEW_PASSWORD:
		case CHANGE_PASSWORD:
		case CHECK_LOGIN_CREDENTIALS:
			__UART_sendByte(UART_READY);
			__UART_receiveString(rx_passwords);

			result = systemPasswordTasks(task_to_do);

			__UART_sendByte(UART_READY);
			__UART_sendByte(result);
			break;

		case OPEN_DOOR:

				_MOTORDC_rotate(CW);
				__TIMER_CTC_startTimer(&timer1_configs);

			break;
			
		case CLOSE_DOOR:

				user_authenticated_flag = FALSE;
				_MOTORDC_rotate(CCW);
				__TIMER_CTC_startTimer(&timer1_configs);

			break;

		default:break;
		}
		/*-------------------------------------------------------------------------*/
	}
}


uint8 systemPasswordTasks(uint8 task_type)
{
	uint8 i, saved_password[6];

	switch( task_type )
	{
	/*-------------------------------------------------------------------------*/
	case SETUP_NEW_PASSWORD:
		/* Check the entered NEW passwords are matching each other */
		for(i=0 ; i<5 ; i++)
		{
			if( rx_passwords[i] != rx_passwords[5+i] )
			{
				return PASSWORD_NOT_MATCHED;
			}
		}
		/******************************************************/
		/* Save new Password in EEPROM */
		for(i=0 ; i<5 ; i++)
		{
			_EXT_EEPROM_writeByte(PASSWORD_MEM_ADDR_LOC+i, rx_passwords[i]);
		}
		/******************************************************/
		break;

		/*-------------------------------------------------------------------------*/
	case CHANGE_PASSWORD:
		/* Fetch saved Password from EEPROM */
		for(i=0 ; i<5 ; i++)
		{
			_EXT_EEPROM_readByte(PASSWORD_MEM_ADDR_LOC+i, saved_password+i);
		}
		/******************************************************/
		/* Check Saved Password matches the user entered old password */
		for(i=0 ; i<5 ; i++)
		{
			if( rx_passwords[i] != saved_password[i] )
			{
				return PASSWORD_NOT_MATCHED;
			}
		}
		/******************************************************/
		/* Check the entered NEW passwords are matching each other */
		for(i=5 ; i<10 ; i++)
		{
			if( rx_passwords[i] != rx_passwords[5+i] )
			{
				return PASSWORD_NOT_MATCHED;
			}
		}
		/******************************************************/
		/* Save new sent Password in EEPROM */
		for(i=5 ; i<10 ; i++)
		{
			_EXT_EEPROM_writeByte(PASSWORD_MEM_ADDR_LOC+i, rx_passwords[i]);
		}
		/******************************************************/
		break;

		/*-------------------------------------------------------------------------*/
	case CHECK_LOGIN_CREDENTIALS:
		/* Fetch saved Password from EEPROM */
		for(i=0 ; i<5 ; i++)
		{
			_EXT_EEPROM_readByte(PASSWORD_MEM_ADDR_LOC+i, saved_password+i);
		}
		/******************************************************/
		/* Check the entered password matches existing password */
		for(i=0 ; i<5 ; i++)
		{
			if( rx_passwords[i] != saved_password[i] )
			{
				return PASSWORD_NOT_MATCHED;
			}
		}
		/******************************************************/
		/* User Authenticated Successfully: Enable MOTOR Access */
		user_authenticated_flag = TRUE;
		/******************************************************/
		break;

		/*-------------------------------------------------------------------------*/
	default: /*Do nothing*/
		break;
		/*-------------------------------------------------------------------------*/
	}

	return TASK_SUCCEED;
}

void TIMER1_ISR_function(void)
{
	_MOTORDC_rotate(OFF);
	__TIMER_CTC_stopTimer(TIMER1);
}
