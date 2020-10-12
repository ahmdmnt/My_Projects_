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

/* ---UART Registers--- */
#define UDR    *((volatile uint8 *const)0x2C)
#define UCSRA  *((volatile uint8 *const)0x2B)
#define UCSRB  *((volatile uint8 *const)0x2A)
#define UCSRC  *((volatile uint8 *const)0x40)
#define UBRRL  *((volatile uint8 *const)0x29)
#define UBRRH  *((volatile uint8 *const)0x40)
/******************************************/

/* ---TWI/I2C Registers--- */
#define TWBR  *((volatile uint8 *const)0x20)
#define TWCR  *((volatile uint8 *const)0x56)
#define TWSR  *((volatile uint8 *const)0x21)
#define TWDR  *((volatile uint8 *const)0x23)
#define TWAR  *((volatile uint8 *const)0x22)
/******************************************/

/*****************************************************************************/
/**** Defined Symbolic Constants ****/
/***DIO Pins***/
#define DDR_A 0
#define DDR_B 1
#define DDR_C 2
#define DDR_D 3
/*****************/
#define PIN_A 0
#define PIN_B 1
#define PIN_C 2
#define PIN_D 3
/*****************/
#define PORT_A 0
#define PORT_B 1
#define PORT_C 2
#define PORT_D 3
/*****************/
#define PA0     0
#define PA1     1
#define PA2     2
#define PA3     3
#define PA4     4
#define PA5     5
#define PA6     6
#define PA7     7
/*****************/
#define PB0     0
#define PB1     1
#define PB2     2
#define PB3     3
#define PB4     4
#define PB5     5
#define PB6     6
#define PB7     7
/*****************/
#define PC0     0
#define PC1     1
#define PC2     2
#define PC3     3
#define PC4     4
#define PC5     5
#define PC6     6
#define PC7     7
/*****************/
#define PD0     0
#define PD1     1
#define PD2     2
#define PD3     3
#define PD4     4
#define PD5     5
#define PD6     6
#define PD7     7
/***External Interrupts Pins***/
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3
#define ISC2  0
#define INT0  6
#define INT1  7
#define INT2  5
#define INTF0 6
#define INTF1 7
#define INTF2 5
/***Timer0 Pins***/
#define CS00  0
#define CS01  1
#define CS02  2
#define WGM01 3
#define COM00 4
#define COM01 5
#define WGM00 6
#define FOC0  7
#define TOIE0 0
#define OCIE0 1
#define TOV0  0
#define OCF0  1
/***Timer1 Pins***/
#define WGM10   0
#define WGM11   1
#define FOC1B   2
#define FOC1A   3
#define COM1B0  4
#define COM1B1  5
#define COM1A0  6
#define COM1A1  7
#define CS10    0
#define CS11    1
#define CS12    2
#define WGM12   3
#define WGM13   4
#define ICES1   6
#define ICNC1   7
#define TOIE1   2
#define OCIE1B  3
#define OCIE1A  4
#define TICIE1  5
#define TOV1    2
#define OCF1B   3
#define OCF1A   4
#define ICF1    5
/*****************/
/***ADC Pins***/
#define REFS1   7
#define REFS0   6
#define ADLAR   5
#define MUX4    4
#define MUX3    3
#define MUX2    2
#define MUX1    1
#define MUX0    0
#define ADEN    7
#define ADSC    6
#define ADATE   5
#define ADIF    4
#define ADIE    3
#define ADPS2   2
#define ADPS1   1
#define ADPS0   0
#define ADTS2   7
#define ADTS1   6
#define ADTS0   5
/*****************/
/***UART Pins***/
#define URSEL   7
#define UMSEL   6
#define UPM1    5
#define UPM0    4
#define USBS    3
#define UCSZ1   2
#define UCSZ0   1
#define UCPOL   0
#define RXC     7
#define TXC     6
#define UDRE    5
#define FE      4
#define DOR     3
#define PE      2
#define U2X     1
#define MPCM    0
#define RXCIE   7
#define TXCIE   6
#define UDRIE   5
#define RXEN    4
#define TXEN    3
#define UCSZ2   2
#define RXB8    1
#define TXB8    0
/*****************/
/***TWI/I2C Pins***/
#define TWBR7   7
#define TWBR6   6
#define TWBR5   5
#define TWBR4   4
#define TWBR3   3
#define TWBR2   2
#define TWBR1   1
#define TWBR0   0
#define TWINT   7
#define TWEA    6
#define TWSTA   5
#define TWSTO   4
#define TWSTC   3
#define TWEN    2
#define TWIE    0
#define TWS7    7
#define TWS6    6
#define TWS5    5
#define TWS4    4
#define TWS3    3
#define TWPS1   1
#define TWPS0   0
/*****************/

/* ----------------------------------END----------------------------------- */

#endif /* REGISTERS_H_ */
