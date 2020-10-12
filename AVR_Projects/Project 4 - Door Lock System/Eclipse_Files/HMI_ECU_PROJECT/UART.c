/**********************************************************************************************
 * UART.c
 * 
 *		**UART - Driver**
 *      Designed for AVR ATmega16 Microcontroller
 *
 *  Created on: Sep 6, 2020
 *      Author: Ahmed Montasser
 ***********************************************************************************************/

/** Used Directives **********************************************************/
#include "UART.h"
/*****************************************************************************/


/** MACRO Definitions ********************************************************/
#define UBRR_VALUE_CALC(BAUD_RATE) (((F_CPU / (BAUD_RATE * 8UL))) - 1)
/*****************************************************************************/


/** Functions Definitions ****************************************************/

/*** Description:-
 * Function Used to Enable UART Module with the given needed configurations
 *  - baud_rate: 100 / 200 / 300 / 1200 / 2400 / 4800 / 9600 / 19200 / 38400 / 57600 / 115200
 *  - data_size: 5 / 6 / 7 / 8 / 9
 *  - stop_bit: TWO_STOP_BITS / TWO_STOP_BITS
 *  - parity: EVEN_PARITY / ODD_PARITY */
void __UART_init(const UART_config *p_uart_config)
{
    /*Enable Parity Error LED O/P for Error Indication*/
    #if(PARITY_ENABLE)
    SET_BIT(PARITY_ERROR_DDR, PARITY_ERROR_PIN);
    #endif
    /*UART Double Speed Transmission*/
    SET_BIT(UCSRA, U2X);
    /********************UCSRB Register Description********************
     * According to Static Config adjust (RXCIE) Rx Complete Interrupt Enable bit
     * Disable (TXCIE) Tx Complete Interrupt Enable bit
     * According to Static Config adjust (UDRIE) Data Register Empty Interrupt Enable
     * Enable (RXEN) Receiver Enable bit.
     * Enable (TXEN) Transmitter Enable bit.
     * Disable (UCSZ2) Data Frame according to config maximum adjusted with 8 bits (Not Needed)
     * (RXB8) / (TXB8) Transmitter/Receiver Data Bit 8 (IGNORED)
     *****************************************************************/
    /*if module configured to Use ISR in RX mode, Enable Rx Complete Interrupt Enable bit*/
    #ifdef RX_ISR_BASED
        SET_BIT(UCSRB, RXICE);
    #endif
    /*Enable Module for Transmitting*/
    SET_BIT(UCSRB, TXEN);
    /*Enable Module for Receiving*/
    SET_BIT(UCSRB, RXEN);

    /********************UCSRC Register Description********************
     * The URSEL must be one when writing the UCSRC.
     * UMSEL Bit Settings: Asynchronous Operation.
     * UPM1:0: Parity Mode: According to Function Configs.
     * USBS: Stop Bit Select: According to Function Configs.
     * UCSZ1:0: Character Size: According to Function Configs.
     * UCPOL: Clock Polarity: According to Static Config
     *****************************************************************/  
    /*Select UCSRC URSEL=1*/
    SET_BIT(UCSRC, URSEL);
    /*Adjust Data Size in frame*/
    UCSRC = (UCSRC&0b11111001) | ((p_uart_config->data_size&0b00000011)<<1);
    /*Set UART in ASYNC Mode*/
    CLR_BIT(UCSRC, UMSEL);
    /*Set UART parity Mode*/
    UCSRC = (UCSRC&0b11001111) | ((p_uart_config->parity)<<4);
    /*Set Stop Bit Config*/
    UCSRC = (UCSRC&0b11110111) | ((p_uart_config->stop_bit)<<3);
    /*Adjust Clock Polarity bit Clear bit if TX_RISING_RX_FALLING, Set bit if TX_FALLING_RX_RISING*/
    #if(CLOCK_POLARITY==TX_FALLING_RX_RISING)
        SET_BIT(UCSRC, UCPOL);
    #endif

    /****************UBRRH and UBRRL Registers Description**************
     * The URSEL must be zero when writing the UBRRH.
     * UBRR11:0: USART Baud Rate Register, adjust 12 bit with desired baudrate
     *****************************************************************/ 
    CLR_BIT(UBRRH, URSEL);
    UBRRL = (uint8)(UBRR_VALUE_CALC(p_uart_config->baud_rate));
    UBRRH = (UBRR_VALUE_CALC(p_uart_config->baud_rate))>>8;
}


/*** Description:-
 * Function used to send a byte*/
void __UART_sendByte(const uint8 u8Data)
{
    /*Delay made to make sure the UDR Register is Empty before Transmitting*/
    while( READ_BIT(UCSRA, UDRE)==LOW );
    /*Put desired message in UDR Register to be sent*/
    UDR = u8Data;
}


/*** Description:-
 * Function used to send a string, pass string array_name by address*/
void __UART_sendString(const uint8 *p_string)
{
    while( *p_string != '\0' )
    {
        __UART_sendByte(*p_string);
        p_string++;
    }
}

#ifdef RX_POLLING_BASED 

    /*** Description:-
     * Function used to receive a byte*/
    uint8 __UART_receiveByte(void)
    {
        /*Delay made to make sure the UDR Register has unread received message*/
        while( READ_BIT(UCSRA, RXC)==LOW );


        if( READ_BIT(UCSRA, PE)==LOW )
        {
            /*fetch the received message*/
            return UDR;
        }
        else
        {
            #if(PARITY_ENABLE)
            SET_BIT(PARITY_ERROR_PORT, PARITY_ERROR_PIN);
            #endif
            return 0; 
        }
    }


    /*** Description:-
     * -IMPORTANT_NOTE__Send String Size at beginning before sending string
     * Function used to receive whole string, pass string{Array_name} By address 
     * and function will fill that variable with received values*/
    void __UART_receiveString(uint8 *p_string)
    {
        uint8 i=0,string_size;

        /*Receive First the String Size*/
        string_size = __UART_receiveByte();

        /*Fill the passed array by address with received string*/
        for(i=0 ; i<string_size ; i++)
        {
            *p_string = __UART_receiveByte();
            p_string++;
        }

        /*Add NULL Terminator at the end of String*/
        *p_string = '\0';
    }
#endif

#ifdef RX_ISR_BASED
void __UART_receiveByte()
{

}
void __UART_receiveString()
{
    
}
#endif
/*****************************************************************************/
