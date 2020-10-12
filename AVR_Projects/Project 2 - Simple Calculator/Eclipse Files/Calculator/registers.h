/*****************************************************************************
 * registers.h
 *  ** Common - Platform Register Definitions **
 *     --------------------------------------
 * 		File contains the AVR [ATmega16] Memory Mapped Registers.
 * 		(Special function registers)
 *
 *  Created on: Sep 6, 2020
 *      Author: Ahmed Montasser
 *****************************************************************************/

#ifndef REGISTERS_H_
#define REGISTERS_H_

/* --------------------Register Mapping Definition-------------------- */

#define SREG  *((volatile uint8 *const)0x5F)
#define I_BIT 7

/* ---DIO Registers--- */
/*Port-A Registers*/
#define PINA  *((volatile uint8 *const)0x39)
#define DDRA  *((volatile uint8 *const)0x3A)
#define PORTA *((volatile uint8 *const)0x3B)
/*Port-B Registers*/
#define PINB  *((volatile uint8 *const)0x36)
#define DDRB  *((volatile uint8 *const)0x37)
#define PORTB *((volatile uint8 *const)0x38)
/*Port-C Registers*/
#define PINC  *((volatile uint8 *const)0x33)
#define DDRC  *((volatile uint8 *const)0x34)
#define PORTC *((volatile uint8 *const)0x35)
/*Port-D Registers*/
#define PIND  *((volatile uint8 *const)0x30)
#define DDRD  *((volatile uint8 *const)0x31)
#define PORTD *((volatile uint8 *const)0x32)
/***********************************************/

/* ---External Interrupt Registers--- */
#define MCUCR  *((volatile uint8 *const)0x55)
#define MCUCSR *((volatile uint8 *const)0x54)
#define GICR   *((volatile uint8 *const)0x5B)
#define GIFR   *((volatile uint8 *const)0x5A)
/******************************************/

/* ---TIMER Registers--- */
/*TIMER0 Registers*/
#define TCCR0  *((volatile uint8 *const)0x53)
#define TCNT0  *((volatile uint8 *const)0x52)
#define OCR0   *((volatile uint8 *const)0x5C)
#define TIMSK  *((volatile uint8 *const)0x59)
#define TIFR   *((volatile uint8 *const)0x58)
#define SFIOR  *((volatile uint8 *const)0x50)
/*TIMER1 Registers*/
#define TCNT1  *((volatile uint16 *const)0x4C)
#define OCR1A  *((volatile uint16 *const)0x4A)
#define OCR1B  *((volatile uint16 *const)0x48)
#define ICR1   *((volatile uint16 *const)0x46)
#define TCCR1A *((volatile uint8 *const)0x4F)
#define TCCR1B *((volatile uint8 *const)0x4E)
#define TCNT1H *((volatile uint8 *const)0x4D)
#define TCNT1L *((volatile uint8 *const)0x4C)
#define OCR1AH *((volatile uint8 *const)0x4B)
#define OCR1AL *((volatile uint8 *const)0x4A)
#define OCR1BH *((volatile uint8 *const)0x49)
#define OCR1BL *((volatile uint8 *const)0x48)
#define ICR1H  *((volatile uint8 *const)0x47)
#define ICR1L  *((volatile uint8 *const)0x46)
/*TIMER2 Registers*/

/******************************************/

/* ---ADC Registers--- */
#define ADMUX   *((volatile uint8 *const)0x27)
#define ADCSRA  *((volatile uint8 *const)0x26)
#define ADC     *((volatile uint16 *const)0x24)
#define ADCH    *((volatile uint8 *const)0x25)
#define ADCL    *((volatile uint8 *const)0x24)
/******************************************/

/* ----------------------------------END----------------------------------- */

#endif /* REGISTERS_H_ */
