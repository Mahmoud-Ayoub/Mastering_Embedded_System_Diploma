﻿/*
 * LCD.h
 *
 *  Author: Mahmoud-Ayoub
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "../../MCAL/DIO/DIO_Config.h"
#include <util/delay.h>


#define Rs	1
#define RW	2
#define EN  3
#define D4	4
#define D5	5
#define D6	6
#define D7	7

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