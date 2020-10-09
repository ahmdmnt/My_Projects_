/***************************************************************************************************
 * appl_hmi_ecu.c
 * 		Application Software for System Human-Interface ECU.
 * 			- Controlling LCD Display
 * 			- Controlling Keypad 3x4
 * 			- Controlling Input Buttons
 * 			- Send needed Data for Control-ECU through UART
 *
 *  Created on: Sep 29, 2020
 *      Author: Ahmed Montasser
 **************************************************************************************************/

//System CPU = 8MHz
#include "DIO.h"
#include "external_interrupt.h"
#include "keypad.h"
#include "LCD.h"
#include "UART.h"

//#define DF_CPU 8000000

#define  FOREVER 				1
#define  NEW_PASSWORD_SETUP		0
#define  CHANGE_PASSWORD_SETUP	1

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

void systemUserAuthenticate(void);
uint8 systemPasswordSetup(uint8 password_setup);
void externalInterrupt0_CloseButton_ISRFunc(void);
void externalInterrupt1_OpenButton__ISRFunc(void);

uint8 Authenticated_FLAG=FALSE;
uint8 passwords_entires[16];
uint8 password_length = 0;

int main(void)
{
	/*-------------------------------------------------------------------------*/
	uint8 pressed_key=0;
	/*-------------------------------------------------------------------------*/
	/*UART Configuration Parameters*/
	UART_config uart_configs = {9600, _8_BIT_DATA, ONE_STOP_BITS, DISABLE_PARITY};
	/*-------------------------------------------------------------------------*/

	__DIO_setPinDirection(DDR_C, PC0, OUTPUT_PIN);
	__DIO_writeOutputPinValue(DDR_C, PC0, LOW);

	/*-------------------------------------------------------------------------*/
	/* Initialize External Interrupt Buttons */
	__INT0_init(FALLING_EDGE, EN_PULLUP);
	__INT1_init(FALLING_EDGE, EN_PULLUP);
	__INT0_setISRCallBackFuncPointer(externalInterrupt0_CloseButton_ISRFunc);
	__INT1_setISRCallBackFuncPointer(externalInterrupt1_OpenButton__ISRFunc);

	/* Initialize the ENTER Button */
	__DIO_setPinDirection(DDR_A, PA7, INPUT_PIN);
	__DIO_enableInternalPullupResistance(PORT_A, PA7);

	/* Initialize LCD Hardware */
	_LCD_init();

	/* Initialize UART Module */
	__UART_init(&uart_configs);
	/*-------------------------------------------------------------------------*/

	/*-------------------------------------------------------------------------*/
	do //while(FOREVER)
	{
		systemPasswordSetup(NEW_PASSWORD_SETUP);
		_LCD_clearScreen();
		_LCD_displayString(" Saving Password...");

		while( __UART_receiveByte() != UART_READY );
		__UART_sendByte(SETUP_NEW_PASSWORD);__DIO_writeOutputPinValue(DDR_C, PC0, 1);

		while( __UART_receiveByte() != UART_READY );
		__UART_sendByte(10);
		__UART_sendString(passwords_entires);//__DIO_writeOutputPinValue(DDR_C, PC0, 0);

		while( __UART_receiveByte() != UART_READY );
		APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;//__DIO_writeOutputPinValue(DDR_C, PC0, 1);

	}while ( __UART_receiveByte != TASK_SUCCEED );
	_LCD_displayString("  Succeeded!");
	/*-------------------------------------------------------------------------*/

	while(FOREVER)
	{
		_LCD_clearScreen();
		//_LCD_adjustCursorPosition(0,0);
		_LCD_displayString("-Select from below options:-");
		_LCD_adjustCursorPosition(1,0);
		_LCD_displayString(" [*]Change Passwd [#]User Authen");

		pressed_key = _KEYPAD_getCurrentPressedKey();
		switch( pressed_key )
		{
		case '*': // User Changing Password
			do //while(FOREVER)
			{
				systemPasswordSetup(CHANGE_PASSWORD_SETUP);
				_LCD_clearScreen();
				_LCD_displayString(" Saving Password...");

				while( __UART_receiveByte() != UART_READY );
				__UART_sendByte(CHANGE_PASSWORD);

				while( __UART_receiveByte() != UART_READY );
				__UART_sendByte(15);
				__UART_sendString(passwords_entires);

				while( __UART_receiveByte() != UART_READY );
				APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;

			}while ( __UART_receiveByte != TASK_SUCCEED );
			_LCD_displayString("  Succeeded!");
			break;

		case '#': // User Login 
			do //while(FOREVER)
			{
				systemUserAuthenticate();
				_LCD_clearScreen();
				_LCD_displayString(" User Login...");

				while( __UART_receiveByte() != UART_READY );
				__UART_sendByte(CHECK_LOGIN_CREDENTIALS);

				while( __UART_receiveByte() != UART_READY );
				__UART_sendByte(5);
				__UART_sendString(passwords_entires);

				while( __UART_receiveByte() != UART_READY );
				APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;

			}while ( __UART_receiveByte != TASK_SUCCEED );
			_LCD_displayString("  Succeeded!");
			_LCD_displayString_atCursor(" >>> Open The Door", 1, 0);
			
			Authenticated_FLAG = TRUE;
			while( Authenticated_FLAG );
			break;
		
		default:
			
			break;
		}
	}
}

void systemUserAuthenticate(void)
{
	password_length=0;

	_LCD_clearScreen();
	_LCD_displayString_atCursor( "Enter Password:-", 0, 0);
	while(FOREVER)
	{
		passwords_entires[password_length] = _KEYPAD_getCurrentPressedKey();
		APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_HALF_SEC_DELAY;

		if(passwords_entires[password_length] >= '0' && passwords_entires[password_length] <= '9')
		{
			_LCD_adjustCursorPosition(1,password_length);
			_LCD_displayCharacter('*');
			password_length++;

			if(password_length == 5)
			{
				passwords_entires[5] = '\0';
				_LCD_displayString_atCursor("SUBMIT?", 0, 25);
				_LCD_displayString_atCursor("Press: Enter", 1, 20);
				while( __DIO_readInputPinValue(PIN_A, PA7)==HIGH );
				password_length=0;
				break;
			}
		}
	}



}

uint8 systemPasswordSetup(uint8 password_setup)
{
	uint8 offset=0; 	
	
	password_length=0;

	if( password_setup == NEW_PASSWORD_SETUP )
	{
		_LCD_displayString("     --> Welcome to DLS <--");
		APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;
		APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;
		APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;
	}
	else if( password_setup == CHANGE_PASSWORD_SETUP )
	{
		_LCD_clearScreen();
		_LCD_displayString_atCursor( "Type Old Password:-", 0, 0);
		while(FOREVER)
		{
			passwords_entires[password_length] = _KEYPAD_getCurrentPressedKey();
			APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_HALF_SEC_DELAY;
			if(passwords_entires[password_length] >= '0' && passwords_entires[password_length] <= '9')
			{
				_LCD_adjustCursorPosition(1,password_length);
				_LCD_displayCharacter('*');
				password_length++;

				if(password_length == 5)
				{
					_LCD_displayString_atCursor("SUBMIT?", 0, 25);
					_LCD_displayString_atCursor("Press: Enter", 1, 20);
					while( __DIO_readInputPinValue(PIN_A, PA7)==HIGH );
					password_length=0;
					break;
				}
			}
		}
	}

	if(password_setup == CHANGE_PASSWORD_SETUP)
	{
		offset = 5;
	}

	_LCD_clearScreen();
	_LCD_displayString_atCursor("Type New Password:-", 0, 0);
	while(FOREVER)
	{
		passwords_entires[offset+password_length] = _KEYPAD_getCurrentPressedKey();
		APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_HALF_SEC_DELAY;
		if(passwords_entires[offset+password_length] >= '0' && passwords_entires[offset+password_length] <= '9')
		{
			_LCD_adjustCursorPosition(1,password_length);
			_LCD_displayCharacter('*');
			password_length++;

			if(password_length == 5)
			{
				_LCD_displayString_atCursor("SUBMIT?", 0, 25);
				_LCD_displayString_atCursor("Press: Enter", 1, 20);
				while( __DIO_readInputPinValue(PIN_A, PA7)==HIGH );
				break;
			}
		}
	}

	_LCD_clearScreen();
	_LCD_displayString_atCursor("Re-type new Password:-", 0, 0);
	while(FOREVER)
	{
		passwords_entires[offset+password_length] = _KEYPAD_getCurrentPressedKey();
		APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_HALF_SEC_DELAY;
		if(passwords_entires[offset+password_length] >= '0' && passwords_entires[offset+password_length] <= '9')
		{
			_LCD_adjustCursorPosition(1,(password_length-5));
			_LCD_displayCharacter('*');
			password_length++;

			if(password_length == 10)
			{
				passwords_entires[offset+password_length] = '\0';
				_LCD_displayString_atCursor("SUBMIT?", 0, 25);
				_LCD_displayString_atCursor("Press: Enter", 1, 20);
				while( __DIO_readInputPinValue(PIN_A, PA7)==HIGH );
				break;
			}
		}
	}

	//	TESTING CODE:-
	//	passwords_entires[offset+password_length]='\0';
	//	_LCD_clearScreen();
	//	_LCD_displayString_atCursor(passwords_entires, 1, 0);
	//	APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;
	//	APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;

	return offset+password_length;
}


void externalInterrupt1_OpenButton__ISRFunc(void)
{
	if(Authenticated_FLAG)
	{
		while( __UART_receiveByte() != UART_READY );
		__UART_sendByte(OPEN_DOOR);

		_LCD_displayString_atCursor(" >>> Door Opened!", 1, 0);
	}
}


void externalInterrupt0_CloseButton_ISRFunc(void)
{
	if(Authenticated_FLAG)
	{
		while( __UART_receiveByte() != UART_READY );
		__UART_sendByte(CLOSE_DOOR);

		_LCD_displayString_atCursor(" >>> Door Closed!", 1, 0);
		Authenticated_FLAG = FALSE;
	}
}

