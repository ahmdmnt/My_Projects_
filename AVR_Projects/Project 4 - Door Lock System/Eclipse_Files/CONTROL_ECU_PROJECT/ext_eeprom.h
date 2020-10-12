/**********************************************************************************************
 * EXT_EEPROM.h
 * 
 *		**EXT_EEPROM - Driver**
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

#ifndef EXT_EEPROM_H_
#define EXT_EEPROM_H_

/** Used Directives **********************************************************/
#include "datatypes.h"
#include "macros.h"
#include "registers.h"
/*****************************************************************************/


/** Macros Declaration ****************************************************/
#define TWI_SUCCESS 1
#define TWI_ERROR  0
/*****************************************************************************/


/** Function Prototypes ******************************************************/

/*** Description:-
 * Function Used to send start bit for a Frame
 */
void  _EXT_EEPROM_init(uint8 master_addr);


/*** Description:-
 *  Frame Structure for Read Byte in Memory:-
 *  +-------+-------------------------------------+-----+---------------+-----+--------+-----+------+
 *  | Start | MEM_ID + addr10 + addr9 + addr8 + W | ACK | addr7...addr0 | ACK | u8Data | ACK | STOP |
 *  +-------+-------------------------------------+-----+---------------+-----+--------+-----+------+
 */
uint8  _EXT_EEPROM_writeByte(uint16 mem_u16addr, uint8 u8Data);


/*** Description:-
 *  Frame Structure for Read Byte in Memory:-
 *  +------------+-------------------------------------+-----+---------------+-----+
 *  |   Start    | MEM_ID + addr10 + addr9 + addr8 + W | ACK | addr7...addr0 | ACK |
 *  +------------+-------------------------------------+-----+---------------+-----+------+
 *  | Rep. Start | MEM_ID + addr10 + addr9 + addr8 + R | ACK |     Data      | ACK | Stop |
 *  +------------+-------------------------------------+-----+---------------+-----+------+
 */
uint8  _EXT_EEPROM_readByte(uint16 mem_u16addr, uint8 *p_u8Data);

/*****************************************************************************/

#endif /* EXT_EEPROM_H_ */
