/**********************************************************************************************
 * ICU.h
 * 
 *		**Input Capture Unit - Driver**
 *      Designed for AVR ATmega16 Microcontroller
 *
 *  Created on: Oct 13, 2020
 *      Author: Ahmed Montasser
 ***********************************************************************************************/

#ifndef ICU_H_
#define ICU_H_

/** Used Directives **********************************************************/
#include "datatypes.h"
#include "macros.h"
#include "registers.h"
/*****************************************************************************/


/** Macros Declaration *******************************************************/
#define FALLING_EDGE    0   
#define RISING_EDGE     1
/*****************************************************************************/


/** Module Configurations ****************************************************/
typedef enum
{
    ICU_NO_CLK, ICU_F_CPU, ICU_F_CPU_8, ICU_F_CPU_64, ICU_F_CPU_256, ICU_F_CPU_1024
}ICU_clock;

typedef struct
{
    uint8 capture_edge;
    ICU_clock clock;
}ICU_config;

/*****************************************************************************/


/** Function Prototypes ******************************************************/


/*** Description:-
 * 	Function initialize the module
 * 	capture_edge : RISING_EDGE, FALLING_EDGE
 * 	clock :  ICU_NO_CLK, ICU_F_CPU, ICU_F_CPU_8, ICU_F_CPU_64, ICU_F_CPU_256, ICU_F_CPU_1024
 */
void __ICU_init(const ICU_config *configs_ptr);


/*** Description:-
 *  Function to set the global pointer to function
 */
void __ICU_setCallBackFunctionGlobalPtr(void (*callBackPtr_ICU_ISR)(void));


/*** Description:-
 *  Function to adjust the detection of capture edge
 */
void __ICU_setCaptureDetectionEdge(const uint8 capture_edge);


/*** Description:-
 *  Get the Time value of capture
 */
uint16 __ICU_getInputCaptureTime(void);


/*** Description:-
 *  Clear timer register, to count from beginning
 */
void __ICU_clearTimerValue(void);

/*** Description:-
 *  De Init the Module
 */
void __ICU_deinit(void);

/*****************************************************************************/

#endif /* ICU_H_ */
