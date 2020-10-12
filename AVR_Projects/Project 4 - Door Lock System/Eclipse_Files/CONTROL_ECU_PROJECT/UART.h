/**********************************************************************************************
 * UART.h
 * 
 *		**UART - Driver**
 *      Designed for AVR ATmega16 Microcontroller
 *
 *  Created on: Sep 6, 2020
 *      Author: Ahmed Montasser
 **********************************************************************************************
 * > When Using this Module :-
 * -----------------------------
 * 1. 
 * 
 **********************************************************************************************/

#ifndef UART_H_
#define UART_H_

/** Used Directives **********************************************************/
#include "datatypes.h"
#include "macros.h"
#include "registers.h"
/*****************************************************************************/


/** Configuration Parameters ***************************************************/
/*** Defined Symbolic Constants ******/
#define ASYNC_MODE
#define DISABLE_PARITY  0
#define EVEN_PARITY     2
#define ODD_PARITY      3
#define TWO_STOP_BITS   1
#define ONE_STOP_BIT    0
#define _5_BIT_DATA     0
#define _6_BIT_DATA     1
#define _7_BIT_DATA     2
#define _8_BIT_DATA     3
#define TX_RISING_RX_FALLING    0
#define TX_FALLING_RX_RISING    1
/*** Static Configurations ******/     /* Edited By Developer */
#define PARITY_ERROR_DDR    DDRD
#define PARITY_ERROR_PORT   PORTD
#define PARITY_ERROR_PIN    PD2
#define PARITY_ENABLE       FALSE
//#define RX_ISR_BASED
#define RX_POLLING_BASED
#define CLOCK_POLARITY  TX_RISING_RX_FALLING
/*****************************************************************************/


/** Externed Global Variables ************************************************/
/*****************************************************************************/


/** Variables Declaration ****************************************************/
typedef struct
{
    uint32 baud_rate; //Values: 100 / 200 / 300 / 1200 / 2400 / 4800 / 9600 / 19200 / 38400 / 57600 / 115200
    uint8  data_size; //Values: _5_BIT_DATA / _6_BIT_DATA / _7_BIT_DATA / _8_BIT_DATA
    uint8  stop_bit;  //Values: ONE_STOP_BIT / TWO_STOP_BITS
    uint8  parity;    //Values: DISABLE_PARITY / EVEN_PARITY / ODD_PARITY
}UART_config;
/*****************************************************************************/


/** Function Prototypes ******************************************************/

/*** Description:-
 * Function Used to Enable UART Module with the given needed configurations
 *  - baud_rate: 100 / 200 / 300 / 1200 / 2400 / 4800 / 9600 / 19200 / 38400 / 57600 / 115200
 *  - data_size: 5 / 6 / 7 / 8 / 9
 *  - stop_bit: ONE_STOP_BIT / TWO_STOP_BITS
 *  - parity: EVEN_PARITY / ODD_PARITY */
void __UART_init(const UART_config *p_uart_config);


/*** Description:-
 * Function used to send a byte*/
void __UART_sendByte(const uint8 u8Data);


/*** Description:-
 * Function used to send whole string*/
void __UART_sendString(const uint8 *p_string);


#ifdef RX_POLLING_BASED 

    /*** Description:-
     * Function used to recevie a byte*/
    uint8 __UART_receiveByte(void);


    /*** Description:-
     * -IMPORTANT_NOTE__Send String Size at beginning before sending string
     * Function used to receive whole string, pass string{Array_name} By address 
     * and function will fill that variable with received values*/
    void __UART_receiveString(uint8 *p_string);

#endif

#ifdef RX_ISR_BASED
void __UART_receiveByte();
void __UART_receiveString();
#endif

/*****************************************************************************/

#endif /* UART_H_ */
