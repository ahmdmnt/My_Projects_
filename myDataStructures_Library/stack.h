/*
 * stack.h
 *
 *  Created on: Oct 13, 2020
 *      Author: Ahmed Montasser
 */

#ifndef STACK_H_
#define STACK_H_

/*----Preprocessor Section--------------------------------------------------------------------*/
#ifndef _DSL_LIB_
#define _DSL_LIB_
	#include <stdio.h>
	#include <stdlib.h>
#endif /* _DSL_LIB_ */

#define NULL_PTR ((void*)0)
#define NEW_NODE_ALLOC(TYPE) (TYPE*)malloc(sizeof(TYPE))
/*--------------------------------------------------------------------------------------------*/


/*----SLL Node Type Definition-----------------------------------------------------------------*/

/* Change the sll_type definition with desired, Ex: typedef <C_DATATYPE> sll_type; */
typedef int stack_type;

/* Node Type Declaration */
struct stack_node
{
	stack_type data;
	struct stack_node *next_node;
};
/*--------------------------------------------------------------------------------------------*/


/*----Extern-ed Global Variable----------------------------------------------------------------*/
extern struct stack_node *stack_head;
/*--------------------------------------------------------------------------------------------*/


/*----Functions Prototypes--------------------------------------------------------------------*/
void STACK_PUSH(stack_type data);
void STACK_POP(void);
stack_type STACK_PEEK(void);
void STACK_print(void);
/*--------------------------------------------------------------------------------------------*/

#endif /* STACK_H_ */
