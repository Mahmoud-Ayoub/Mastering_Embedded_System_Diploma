/*
 * LCD.c
 *
 *  Author: Mahmoud-Ayoub
 */ 

/*
16X2 CHARACTER LCD
DATA LINES
- LCD_D4 >> PORTA .4
- LCD_D5 >> PORTA .5
- LCD_D6 >> PORTA .6
- LCD_D7 >> PORTA .7

CONTROL LINES
- LCD_RS >> PORTB .1
- LCD_RW >> PORTB .2
- LCD_E  >> PORTB .3
*/

#include "LCD.h"

/*
Description : function to initialize LCD port , 4 bits mode , and send required commands for initialization
inputs		: none
outputs		: none
*/
void LCD_init (void) {
	/*
	// Pins Directions
	DIO_SetPinValue(portB , Rs , OUTPUT) ; 
	DIO_SetPinValue(portB , RW , OUTPUT) ;
	DIO_SetPinValue(portB , EN , OUTPUT) ;
	DIO_SetPinValue(portA , D4 , OUTPUT) ;
	DIO_SetPinValue(portA , D5 , OUTPUT) ;
	DIO_SetPinValue(portA , D6 , OUTPUT) ;
	DIO_SetPinValue(portA , D7 , OUTPUT) ;
	*/
	DIO_SetPortDirection(portA , OUTPUT) ; 
	DIO_SetPortDirection(portB , OUTPUT) ;
	// Reset values on LCD Pins
	DIO_SetPinValue(portB, Rs , 0) ;			
	DIO_SetPinValue(portB, RW , 0) ;
	DIO_SetPinValue(portB, EN , 0) ;
	DIO_SetPinValue(portA, D4 , 0) ;
	DIO_SetPinValue(portA, D5 , 0) ;
	DIO_SetPinValue(portA, D6 , 0) ;
	DIO_SetPinValue(portA, D7 , 0) ;
	            
	LCD_send_cmd(0x33) ;			// needed commands for 4 bits mode   (group of initial commands must be sent to LCD)
	LCD_send_cmd(0x32) ;
	LCD_send_cmd(0x28) ;
	LCD_send_cmd(0x0E) ;
	LCD_send_cmd(0x01) ;
	_delay_us(2000) ;
	LCD_send_cmd(0x06) ;
}

/*
Description : function to send command to LCD
inputs		: command
outputs		: none
*/
void LCD_send_cmd (char cmd) {
	
	char command ;
	
	command = (PORTA_REG & 0x0F) | (cmd & 0xF0);	// Sending upper nibble
	DIO_SetPortValue(portA , command) ;
	CLEAR_BIT (PORTB_REG , Rs) ;					// write command
	SET_BIT (PORTB_REG , EN) ;						//  E is set high (telling LCD to receive data)
	_delay_ms(1) ;
	CLEAR_BIT (PORTB_REG , EN) ;						// E is set low (telling LCD that we are done sending data)
	_delay_ms(10) ; 
	
	command = (PORTA_REG & 0x0F) | (cmd << 4);		// Sending lower nibble
	DIO_SetPortValue(portA , command) ;
	CLEAR_BIT (PORTB_REG , Rs) ;					// write command
	SET_BIT (PORTB_REG , EN) ;						//  E is set high (telling LCD to receive data)
	_delay_ms(1) ;
	CLEAR_BIT (PORTB_REG , EN) ;						// E is set low (telling LCD that we are done sending data)
	_delay_ms(10) ;
}

/*
Description : function to send character to LCD
inputs		: char data
outputs		: none
*/
void LCD_send_char (char value) {
	
	char sent_value ; 
	
	sent_value = (PORTA_REG & 0x0F) | (value & 0xF0);/* Sending upper nibble */
	DIO_SetPortValue(portA , sent_value) ;
	SET_BIT (PORTB_REG , Rs) ;						// write data
	SET_BIT (PORTB_REG , EN) ;						//  E is set high (telling LCD to receive data)
	_delay_ms(1) ;
	CLEAR_BIT (PORTB_REG , EN) ;						// E is set low (telling LCD that we are done sending data)
	_delay_ms(10) ;
	
	sent_value = (PORTA_REG & 0x0F) | (value << 4);  /* Sending lower nibble */
	DIO_SetPortValue(portA , sent_value) ;
	SET_BIT (PORTB_REG , Rs) ;						// write data
	SET_BIT (PORTB_REG , EN) ;						//  E is set high (telling LCD to receive data)
	_delay_ms(1) ;
	CLEAR_BIT (PORTB_REG , EN) ;						// E is set low (telling LCD that we are done sending data)
	_delay_ms(10) ;
}

/*
Description : function to send string to LCD
inputs		: string data
outputs		: none
*/
void LCD_send_str (char* str) {
	unsigned int char_index = 0 ; 
	while (str[char_index] != '\0') {
		LCD_send_char(str[char_index]) ; 
		char_index ++ ; 
	}	
}

/*
Description : function to clear the LCD
inputs		: none
outputs		: none
*/
void LCD_clear (void) {
	LCD_send_cmd(0x01) ;         
}

/*
Description : function to Force cursor to beginning of second line
inputs		: none
outputs		: none
*/
void LCD_newline (void) {
	LCD_send_cmd(0xC0) ;
}

/*
Description : function to shift cursor left
inputs		: none
outputs		: none
*/
void LCD_shift_left (void) {
	LCD_send_cmd(0x10) ;
}

/*
Description : function to shift cursor right
inputs		: none
outputs		: none
*/
void LCD_shift_right (void) {
	LCD_send_cmd(0x14) ;
}

/*
Description : function to return cursor to its initial position (0,0)
inputs		: none
outputs		: none
*/
void LCD_home (void) {
	LCD_send_cmd(0x02) ;
}
