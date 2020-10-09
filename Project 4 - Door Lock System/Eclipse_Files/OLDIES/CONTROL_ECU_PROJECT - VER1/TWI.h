/**********************************************************************************************
 * TWI.h
 * 
 *		**TWI - Driver**
 *      Designed for AVR ATmega16 Microcontroller - POLLING BASED
 *
 *  Created on: Sep 6, 2020
 *      Author: Ahmed Montasser
 **********************************************************************************************
 * > When Using this Module :-
 * -----------------------------
 * 1. 
 * 
 **********************************************************************************************/

#ifndef TWI_H_
#define TWI_H_

/** Used Directives **********************************************************/
#include "datatypes.h"
#include "macros.h"
#include "registers.h"
/*****************************************************************************/


/** Configuration Parameters ***************************************************/
/*** Defined Symbolic Constants ******/
#define PRESCALE_1      0
#define PRESCALE_4      1
#define PRESCALE_16     2
#define PRESCALE_64     3
/* I2C Status Bits in the TWSR Register */
#define TWI_START_SENT                  0x08 // A START condition has been transmitted
#define TWI_REP_START_SENT              0x10 // A repeated START condition has been transmitted
#define TWI_MAS_TRAN_SLA_ADR_WRTIE_ACK  0x18 // Slave Addr + Write request has been transmitted; ACK has been received
#define TWI_MAS_TRAN_SLA_ADR_READ_ACK   0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TWI_MAS_TRAN_DATA_ACK           0x28 // Master transmit data and ACK has been received from Slave.
#define TWI_MAS_RECE_DATA_ACK           0x50 // Master received data and send ACK to slave
#define TWI_MAS_RECE_DATA_NACK          0x58 // Master received data but doesn't send ACK to slave
/*** Static Configurations ******/     /* Edited By Developer */
/*****************************************************************************/


/** Externed Global Variables ************************************************/
/*****************************************************************************/


/** Variables Declaration ****************************************************/
typedef struct
{
    uint32 TWPS_value;     //Values: PRESCALE_1 / PRESCALE_4 / PRESCALE_16 / PRESCALE_64
    uint8  TWBR_value;     //Values: values from 0 to 255 decimal
    uint8  TWI_myAddress;  //Values: values from 0 to 112 decimal
}TWI_config;
/*****************************************************************************/


/** Function Prototypes ******************************************************/


/*** Description:-
 * Function Used to Enable TWI Module with the given needed configurations
 *  - Bit Rate Equation = (F_CPU/16+(2*TWBR*PRESCALE_VALUE))
 *  - TWPS_value    : PRESCALE_1 / PRESCALE_4 / PRESCALE_16 / PRESCALE_64
 *  - TWBR_value    : values from 0 to 255
 *  - TWI_myAddress : values from 0 to 128*/
void  __TWI_init(const TWI_config *p_TWI_config);


/*** Description:-
 * Function Used to send start bit for a Frame
 */
void  __TWI_startFrame(void);


/*** Description:-
 *  Function Used to send stop bit for a Frame
 */
void  __TWI_stopFrame(void);


/*** Description:-
 * Function Used to send a Byte bit in a Frame 
 */
void  __TWI_transmitByte(uint8 data); 


/*** Description:-
 * Function Used to receive a Byte bit from a Frame and send ACK
 */
uint8 __TWI_receiveByte_ACK(void);


/*** Description:-
 * Function Used to receive a Byte bit from a Frame and DOESN'T send ACK
 */
uint8 __TWI_receiveByte_NACK(void);


/*** Description:-
 * Function Used to Read Status of the Action done
 */
uint8 __TWI_getStatus(void);

/*****************************************************************************/

#endif /* TWI_H_ */
