/*
 * LCD.h
 *
 *  Author: Mahmoud-Ayoub
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "GPIO.h"

// all LCD pins (data + command) are connected to same PORT (A)
#define LCD_PORT GPIOB
#define Rs  GPIO_PIN_0
#define E   GPIO_PIN_1
#define D4	GPIO_PIN_4
#define D5	GPIO_PIN_5
#define D6	GPIO_PIN_6
#define D7	GPIO_PIN_7

#define MODE 4                      // default mode is 4 bits mode

void LCD_init (void) ;
void LCD_send_cmd (char cmd) ;
void LCD_send_char (char value) ;
void LCD_send_str (char* str) ;
void LCD_clear (void) ;
void LCD_newline (void) ; 
void LCD_shift_left (void) ;
void LCD_shift_right (void) ;
void LCD_home (void) ; 


#endif /* LCD_H_ */
