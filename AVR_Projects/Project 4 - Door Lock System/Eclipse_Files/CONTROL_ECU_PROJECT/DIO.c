/**********************************************************************************************
 * DIO.c
 * 
 *		**DIO - Driver**
 *      Designed for AVR ATmega16 Microcontroller
 *
 *  Created on: Sep 6, 2020
 *      Author: Ahmed Montasser
 ***********************************************************************************************/

/** Used Directives **********************************************************/
#include "DIO.h"
/*****************************************************************************/


/** Variable Definitions *****************************************************/
volatile uint8 *const ddr_regs[4]  = {&DDRA, &DDRB, &DDRC, &DDRD};
volatile uint8 *const pin_regs[4]  = {&PINA, &PINB, &PINC, &PIND};
volatile uint8 *const port_regs[4] = {&PORTA, &PORTB, &PORTC, &PORTD};
/*****************************************************************************/


/** Functions Definitions ****************************************************/

/*** Description:-
 * Adjust the DDR_x Registers for Desired PXX with needed direction */
void  __DIO_setPinDirection(uint8 port_name,uint8 pin_name,uint8 direction)
{
    if( direction == OUTPUT_PIN )
    {
        SET_BIT(*ddr_regs[port_name], pin_name);
    }
    else if( direction == INPUT_PIN )
    {
        CLR_BIT(*ddr_regs[port_name], pin_name);
    }
    else{}
}


/*** Description:-
 * Enable Internal Pullup Resistor for the Input Pin */
void  __DIO_enableInternalPullupResistance(uint8 port_name,uint8 pin_name)
{
    SET_BIT(*port_regs[port_name], pin_name);
}


/*** Description:-
 * Output a Digital Value over the Output Pin */
void  __DIO_writeOutputPinValue(uint8 port_name,uint8 pin_name,uint8 value)
{
    if( value == HIGH )
    {
        SET_BIT(*port_regs[port_name], pin_name);
    }
    else if( value == LOW )
    {
        CLR_BIT(*port_regs[port_name], pin_name);
    }
    else{}
}


/*** Description:-
 * Read and fetch the Digital Value from a Pin */
uint8 __DIO_readInputPinValue(uint8 port_name,uint8 pin_name)
{
    return READ_BIT(*pin_regs[port_name], pin_name);
}


/*** Description:-
 * Toggle the Value of Output Pin */
void  __DIO_toggleOutputPinValue(uint8 port_name,uint8 pin_name)
{
    TGL_BIT(*port_regs[port_name], pin_name);
}


/*** Description:-
 * Adjust the DDR_x Registers for Whole PORT with needed direction */
void  __DIO_setPortDirection(uint8 port_name, uint8 direction)
{
    if( direction == OUTPUT_PORT )
    {
        *ddr_regs[port_name] = 0xFF;
    }
    else if( direction == INPUT_PORT )
    {
        *ddr_regs[port_name] = 0x00;
    }
    else{}
}


/*** Description:-
 * Enable Internal Pullup Resistor for whole PORT Input Pins */
void  __DIO_enablePortInternalPullupResistance(uint8 port_name)
{
    *port_regs[port_name] = 0xFF;
}


/*** Description:-
 * Output a Digital Values over PORT Output Pins */
void  __DIO_writeOutputPortValue(uint8 port_name,uint8 value)
{
    *port_regs[port_name] = value;
}


/*** Description:-
 * Read and fetch the Digital Values from PORT Pins */
uint8 __DIO_readInputPortValue(uint8 port_name)
{
    return *pin_regs[port_name];
}
/*****************************************************************************/



// /*Description: 
//  *  - Group of Pins should start from Px0 not from middle
//  *  - pins_count use the defined MACROS (GROUP_OF_PINS) */
// void  __DIO_setPinGroupDirection(uint8 port_name, uint8 pins_mask, uint8 direction);
// {
//     if( direction == OUTPUT_PORT )
//     {
//         *ddr_regs[port_name] = (*ddr_regs[port_name] & ~(pins_mask)) | (0xFF & pins_mask);
//     }
//     else if( direction == INPUT_PORT )
//     {
//         *ddr_regs[port_name] = (*ddr_regs[port_name] & ~(pins_mask)) | (0x00 & pins_mask);
//     }
//     else{}
// }

// /*Description: 
//  *  - Group of Pins should start from Px0 not from middle
//  *  - pins_count use the defined MACROS (GROUP_OF_PINS) */
// void  __DIO_enablePinGroupInternalPullupResistance(uint8 port_name, uint8 pins_mask)
// {
//     *ddr_regs[port_name] = (*ddr_regs[port_name] & ~(pins_mask)) | (0xFF & pins_mask);
// }

// /*Description: 
//  *  - Group of Pins should start from Px0 not from middle
//  *  - pins_count use the defined MACROS (GROUP_OF_PINS) */
// void  __DIO_writeOutputPinGroupValue(uint8 port_name, uint8 pins_mask, uint8 value)
// {
//     *port_regs[port_name] = (*port_regs[port_name] & ~(pins_mask)) | (value & pins_mask);
// }

// /*Description: 
//  *  - Group of Pins should start from Px0 not from middle
//  *  - pins_count use the defined MACROS (GROUP_OF_PINS) */
// uint8 __DIO_readInputPinGroupValue(uint8 port_name, uint8 pins_mask)
// {
//     return (*pin_regs[port_name] & ~(pins_mask));
// }