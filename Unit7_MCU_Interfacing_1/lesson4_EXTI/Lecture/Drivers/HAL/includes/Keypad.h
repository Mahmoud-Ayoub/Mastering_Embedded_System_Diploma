/*
 * Keypad.h
 *
 *  Author: Mahmoud Ayoub
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_ 

#include "GPIO.h"

#define KEYPAD_PORT	GPIOA
#define OUTPUT_ROW  GPIOA->ODR						// LSB is rows (OUTPUTS)
#define INPUT_COL	GPIOA->IDR >> 4					// MSB is columns (INPUTS)

#define R0		GPIO_PIN_0
#define R1		GPIO_PIN_1
#define R2		GPIO_PIN_2
#define R3		GPIO_PIN_3
#define COL0	GPIO_PIN_4
#define COL1	GPIO_PIN_5
#define COL2	GPIO_PIN_6
#define COL3	GPIO_PIN_7


void KEYPAD_init (void) ; 
char KEYPAD_read (void) ;
void KEYPAD_wait (void) ; 

#endif /* KEYPAD_H_ */
