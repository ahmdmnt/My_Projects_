/**********************************************************************************************
 * TWI.c
 * 
 *		**TWI - Driver**
 *      Designed for AVR ATmega16 Microcontroller
 *
 *  Created on: Sep 6, 2020
 *      Author: Ahmed Montasser
 ***********************************************************************************************/

/** Used Directives **********************************************************/
#include "TWI.h"
/*****************************************************************************/


/** MACRO Definitions ********************************************************/
#define UBRR_VALUE_CALC(BAUD_RATE) (((F_CPU / (BAUD_RATE * 8UL))) - 1)
/*****************************************************************************/


/** Functions Definitions ****************************************************/

/*** Description:-
 * Function Used to Enable TWI Module with the given needed configurations
 *  - Bit Rate Equation = (F_CPU/16+(2*TWBR*PRESCALE_VALUE))
 *  - TWPS_value    : PRESCALE_1 / PRESCALE_4 / PRESCALE_16 / PRESCALE_64
 *  - TWBR_value    : values from 0 to 255
 *  - TWI_myAddress : values from 0 to 128*/
void  __TWI_init(const TWI_config *p_TWI_config)
{
    /*Set the TWBR value for Bitrate adjusting in TWBR Register*/
    TWBR = p_TWI_config->TWBR_value;

    /*Set the TWPS value for Bitrate adjusting in TWBR Register*/
    TWSR = (TWSR&0b11111100) | (p_TWI_config->TWPS_value);

    /*Set the System Module Identification Address*/
    TWAR = p_TWI_config->TWI_myAddress;

    /*Enable TWI Module TWI Enable Pin*/
    SET_BIT(TWCR, TWEN);
}


/*** Description:-
 * Function Used to send start bit for a Frame
 */
void  __TWI_startFrame(void)
{
    /*Clear the Interrupt flag of last Operation, TWI Module ready to execute another Operation
     * - TWINT = 1
     *Send the Start Bit of a Frame, Master Initiating Communication
     * - TWSTA = 1
     *Re-Enable TWI Module again
     * - TWEN = 1
     *Disable and Clear any other bit in the Register
     */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while( READ_BIT(TWCR,TWINT)==LOW );
}


/*** Description:-
 *  Function Used to send stop bit for a Frame
 */
void  __TWI_stopFrame(void)
{
    /*Clear the Interrupt flag of last Operation, TWI Module ready to execute another Operation
     * - TWINT = 1
     *Send the Start Bit of a Frame, Master Initiating Communication
     * - TWSTO = 1
     *Re-Enable TWI Module again
     * - TWEN = 1
     *Disable and Clear any other bit in the Register
     */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    
    /* No Need to wait after stop frame bit, TWI won't be used */
}


/*** Description:-
 * Function Used to send a Byte bit in a Frame 
 */
void  __TWI_transmitByte(uint8 data)
{
    /*Send data in TWDR Register to be ready for transmission*/
    TWDR = data;

    /*Clear the Interrupt flag of last Operation, TWI Module ready to execute another Operation
     * - TWINT = 1
     *Re-Enable TWI Module again
     * - TWEN = 1
     *Disable and Clear any other bit in the Register
     */
    TWCR = (1 << TWINT) | (1 << TWEN);
    
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while( READ_BIT(TWCR,TWINT)==LOW );    
}


/*** Description:-
 * Function Used to receive a Byte bit from a Frame and send ACK
 */
uint8 __TWI_receiveByte_ACK(void)
{
    /*Clear the Interrupt flag of last Operation, TWI Module ready to execute another Operation
     * - TWINT = 1
     *Enable the Acknowledgment bit upon receiving a byte
     * - TWEA = 1
     *Re-Enable TWI Module again
     * - TWEN = 1
     *Disable and Clear any other bit in the Register
     */
    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);

    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while( READ_BIT(TWCR,TWINT)==LOW );

    /*fetch the received Data*/
    return TWDR;
}


/*** Description:-
 * Function Used to receive a Byte bit from a Frame and DOESN'T send ACK
 */
uint8 __TWI_receiveByte_NACK(void)
{
    /*Clear the Interrupt flag of last Operation, TWI Module ready to execute another Operation
     * - TWINT = 1
     *Re-Enable TWI Module again
     * - TWEN = 1
     *Disable and Clear any other bit in the Register
     */
    TWCR = (1 << TWINT) | (1 << TWEN);

    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while( READ_BIT(TWCR,TWINT)==LOW);

    /*fetch the received Data*/
    return TWDR;
}


/*** Description:-
 * Function Used to Read Status of the Action done
 */
uint8 __TWI_getStatus(void)
{
    uint8 status;

    /* Masking to eliminate first 3 bits and read the HEXA Values as it is */
    status = TWSR & 0xF8;
    
    return status;
}
/*****************************************************************************/
