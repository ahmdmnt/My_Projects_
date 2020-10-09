/**********************************************************************************************
 * EXT_EEPROM.c
 * 
 *		**EXT_EEPROM - Driver**
 *      Designed for AVR ATmega16 Microcontroller
 *
 *  Created on: Sep 6, 2020
 *      Author: Ahmed Montasser
 ***********************************************************************************************/

/** Used Directives **********************************************************/
#include "EXT_EEPROM.h"
#include "TWI.h"
/*****************************************************************************/


/** MACRO Definitions ********************************************************/
#define EEPROM_TWBR_VALUE   0x02
#define EEPROM_TWPS_VALUE   PRESCALE_1
/*****************************************************************************/


/** Functions Definitions ****************************************************/

/*** Description:-
 * Function Used to send start bit for a Frame
 */
void  _EXT_EEPROM_init(uint8 master_addr)
{
    /*Define the TWI Configuration Parameters*/
    TWI_config eeprom_twi_config = {EEPROM_TWPS_VALUE, EEPROM_TWBR_VALUE, 0x00};
    eeprom_twi_config.TWI_myAddress = master_addr;

    /*Init the TWI Module*/
    __TWI_init(&eeprom_twi_config);
}


/*** Description:-
 *  Frame Structure for Read Byte in Memory:-
 *  +-------+-------------------------------------+-----+---------------+-----+--------+-----+------+
 *  | Start | MEM_ID + addr10 + addr9 + addr8 + W | ACK | addr7...addr0 | ACK | u8Data | ACK | STOP |
 *  +-------+-------------------------------------+-----+---------------+-----+--------+-----+------+
 */
uint8  _EXT_EEPROM_writeByte(uint16 mem_u16addr, uint8 u8Data)
{
    __TWI_startFrame();
    if( __TWI_getStatus() != TWI_START_SENT )
    {
        return TWI_ERROR;
    }

    __TWI_transmitByte( (uint8)((0xA0) | ((mem_u16addr & 0x0700)>>7)) );
    if( __TWI_getStatus() != TWI_MAS_TRAN_SLA_ADR_WRTIE_ACK )
    {
        return TWI_ERROR;
    }

    __TWI_transmitByte( (uint8)(mem_u16addr) );
    if( __TWI_getStatus() != TWI_MAS_TRAN_DATA_ACK )
    {
        return TWI_ERROR;
    }

    __TWI_transmitByte(u8Data);
    if( __TWI_getStatus() != TWI_MAS_TRAN_DATA_ACK )
    {
        return TWI_ERROR;
    }

    __TWI_stopFrame();

    return TWI_SUCCESS;
}


/*** Description:-
 *  Frame Structure for Read Byte in Memory:-
 *  +------------+-------------------------------------+-----+---------------+-----+
 *  |   Start    | MEM_ID + addr10 + addr9 + addr8 + W | ACK | addr7...addr0 | ACK |
 *  +------------+-------------------------------------+-----+---------------+-----+------+
 *  | Rep. Start | MEM_ID + addr10 + addr9 + addr8 + R | ACK |     Data      | ACK | Stop |
 *  +------------+-------------------------------------+-----+---------------+-----+------+
 */
uint8  _EXT_EEPROM_readByte(uint16 mem_u16addr, uint8 *p_u8Data)
{
    __TWI_startFrame();
    if( __TWI_getStatus() != TWI_START_SENT )
    {
        return TWI_ERROR;
    }

    __TWI_transmitByte( (uint8)(((mem_u16addr & 0x0700)>>7)) | (0xA0));
    if( __TWI_getStatus() != TWI_MAS_TRAN_SLA_ADR_WRTIE_ACK )
    {
        return TWI_ERROR;
    }

    __TWI_transmitByte( (uint8)(mem_u16addr) );
    if( __TWI_getStatus() != TWI_MAS_TRAN_DATA_ACK )
    {
        return TWI_ERROR;
    }

    __TWI_startFrame();
    if( __TWI_getStatus() != TWI_REP_START_SENT )
    {
        return TWI_ERROR;
    }

    __TWI_transmitByte( (uint8)(((mem_u16addr & 0x0700)>>7)) | (0xA0) | 1);
    if( __TWI_getStatus() != TWI_MAS_TRAN_SLA_ADR_READ_ACK )
    {
        return TWI_ERROR;
    }

    *p_u8Data = __TWI_receiveByte_NACK();
    if( __TWI_getStatus() != TWI_MAS_RECE_DATA_NACK )
    {
        return TWI_ERROR;
    }

    __TWI_stopFrame();

    return TWI_SUCCESS;    
}

/*****************************************************************************/
