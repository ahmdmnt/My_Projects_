///***************************************************************************************************
// * hmi_ecu_appl.c
// * 		Application Software for System Human-Interface ECU.
// * 			- Controlling LCD Display
// * 			- Controlling Keypad 3x4
// * 			- Controlling Input Buttons
// * 			- Send needed Data for Control-ECU through UART
// *
// *  Created on: Sep 29, 2020
// *      Author: Ahmed Montasser
// **************************************************************************************************/
//
//
//
///* Preprocessor Section ***************************************************************************/
////#include "datatypes.h"
////#include "DIO.h"
////#include "external_interrupt.h"
//#include "UART.h"
////#include "LCD.h"
////#include "keypad.h"
//
//
///* Application S/W #defines */
//#define FOREVER                       0x01
//
///* Table of defined Communication Messages between the two ECUs */
//#define UART_READY	                  0xFF
//
////Received Messages from HMI-ECU:-
//#define SETUP_NEW_PASSWORD		      0x01
//#define CHANGE_PASSWORD			      0x02
//#define CHECK_LOGIN_CREDENTIALS	      0x03
//#define OPEN_DOOR				      0x04
//#define CLOSE_DOOR				      0x05
//
////Replies Sent to HMI-ECU:-
//#define PASSWORD_SAVED			      0x11
//#define USER_AUTHENTICATED            0x12
//#define PASSWORD_NOT_MATCHED	      0x21
///**************************************************************************************************/
//
//
//
///* Global Variables *******************************************************************************/
//uint8 tx_password[16];
///**************************************************************************************************/
//
//
//
///* Functions Declaration **************************************************************************/
//
///**************************************************************************************************/
//
//
//
///* APPL Software: MAIN FUNCTION *******************************************************************/
//int main(void)
//{
//	uint8 task_status;
//
//    /*UART Configuration Parameters*/
//	UART_config uart_configs = {9600, _8_BIT_DATA, ONE_STOP_BIT, DISABLE_PARITY};
//
//    /* Initialize UART Module */
//    __UART_init(&uart_configs);
//
//
//    tx_password[0]='1';
//    tx_password[1]='1';
//    tx_password[2]='1';
//    tx_password[3]='1';
//    tx_password[4]='1';
//    tx_password[5]='1';
//    tx_password[6]='1';
//    tx_password[7]='1';
//    tx_password[8]='1';
//    tx_password[9]='0';
//    tx_password[10]='\0';
//
////*****************************************************************************************
//
//    while( __UART_receiveByte() != UART_READY );
//    __UART_sendByte(SETUP_NEW_PASSWORD);
//
//    while( __UART_receiveByte() != UART_READY );
//    __UART_sendByte(10);
//    __UART_sendString(tx_password);
//
//    if( __UART_receiveByte() == PASSWORD_NOT_MATCHED )
//    {
//    	tx_password[9]='1';
//    	while( __UART_receiveByte() != UART_READY );
//    	__UART_sendByte(SETUP_NEW_PASSWORD);
//
//    	while( __UART_receiveByte() != UART_READY );
//    	__UART_sendByte(10);
//    	__UART_sendString(tx_password);
//    }
//
////*****************************************************************************************
//
////*****************************************************************************************
//    while( __UART_receiveByte() != UART_READY );
//    __UART_sendByte(CHECK_LOGIN_CREDENTIALS);
//
//    tx_password[4]='0';
//    tx_password[5]='\0';
//    while( __UART_receiveByte() != UART_READY );
//    __UART_sendByte(5);
//    __UART_sendString(tx_password); //1st trial
//
//    if( __UART_receiveByte() == PASSWORD_NOT_MATCHED )
//    {
//    	tx_password[4]='2';
//    	while( __UART_receiveByte() != UART_READY );
//    	__UART_sendByte(CHECK_LOGIN_CREDENTIALS);
//
//    	while( __UART_receiveByte() != UART_READY );
//    	__UART_sendByte(5);
//    	__UART_sendString(tx_password); //2nd trial
//    }
//
//    if( __UART_receiveByte() == PASSWORD_NOT_MATCHED )
//    {
//    	tx_password[4]='1';
//    	while( __UART_receiveByte() != UART_READY );
//    	__UART_sendByte(CHECK_LOGIN_CREDENTIALS);
//
//    	while( __UART_receiveByte() != UART_READY );
//    	__UART_sendByte(5);
//    	__UART_sendString(tx_password); ////3rd trial
//    }
////*****************************************************************************************
//
//
////*****************************************************************************************
//    while( __UART_receiveByte() != UART_READY );
//    __UART_sendByte(OPEN_DOOR);
////*****************************************************************************************
//    APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;
//    APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;
//    APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;
//    APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;
//    APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;APPROX_1SEC_DELAY;
////*****************************************************************************************
//    while( __UART_receiveByte() != UART_READY );
//    __UART_sendByte(CLOSE_DOOR);
////*****************************************************************************************
//
//    while(FOREVER)
//    {
//
//
//    }
//
//    return 0;
//
//}
///**************************************************************************************************/
