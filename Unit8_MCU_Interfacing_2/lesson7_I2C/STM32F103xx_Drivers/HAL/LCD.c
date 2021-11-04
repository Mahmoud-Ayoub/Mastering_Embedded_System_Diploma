/*
 * LCD.c
 *
 *  Author: Mahmoud-Ayoub
 */ 
#include "LCD.h"


void wait_ms (uint32_t time) {
	uint32_t i , j ;
	for (i=0 ; i<time ; i++) {
		for (j=0 ; j<255 ; j++) ;
	}
}

/*
Description : function to initialize LCD port , 4 bits mode , and send required commands for initialization
inputs		: none
outputs		: none
 */
void LCD_init (void) {
	GPIO_PinConfig_t RS_config ;
	RS_config.GPIO_PinNumber = Rs ;
	RS_config.GPIO_MODE = GPIO_MODE_OUTPUT_PUSH_PULL ;
	RS_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT, &RS_config) ;

	GPIO_PinConfig_t EN_config ;
	EN_config.GPIO_PinNumber = E ;
	EN_config.GPIO_MODE = GPIO_MODE_OUTPUT_PUSH_PULL ;
	EN_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT, &EN_config) ;

	GPIO_PinConfig_t D4_config ;
	D4_config.GPIO_PinNumber = D4 ;
	D4_config.GPIO_MODE = GPIO_MODE_OUTPUT_PUSH_PULL ;
	D4_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT, &D4_config) ;

	GPIO_PinConfig_t D5_config ;
	D5_config.GPIO_PinNumber = D5 ;
	D5_config.GPIO_MODE = GPIO_MODE_OUTPUT_PUSH_PULL ;
	D5_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT, &D5_config) ;

	GPIO_PinConfig_t D6_config ;
	D6_config.GPIO_PinNumber = D6 ;
	D6_config.GPIO_MODE = GPIO_MODE_OUTPUT_PUSH_PULL ;
	D6_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT, &D6_config) ;

	GPIO_PinConfig_t D7_config ;
	D7_config.GPIO_PinNumber = D7 ;
	D7_config.GPIO_MODE = GPIO_MODE_OUTPUT_PUSH_PULL ;
	D7_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT, &D7_config) ;


	LCD_send_cmd(0x33) ;			// needed commands for 4 bits mode   (group of initial commands must be sent to LCD)
	LCD_send_cmd(0x32) ;
	LCD_send_cmd(0x28) ;
	LCD_send_cmd(0x0E) ;
	LCD_send_cmd(0x01) ;
	wait_ms(2);
	LCD_send_cmd(0x06) ;
}

/*
Description : function to send command to LCD
inputs		: command
outputs		: none
 */
void LCD_send_cmd (char cmd) {

	char command ;

	command = (LCD_PORT->ODR & 0x0F) | (cmd & 0xF0);	// Sending upper nibble
	MCAL_GPIO_WritePort(LCD_PORT, command) ;
	//DIO_SetPortValue(portC , command) ;

	MCAL_GPIO_WritePin(LCD_PORT, Rs, GPIO_PIN_RESET) ;
	//CLEAR_BIT (PORTC_REG , Rs) ;					// write command

	MCAL_GPIO_WritePin(LCD_PORT, E, GPIO_PIN_SET) ;
	//SET_BIT (PORTC_REG , E) ;						//  E is set high (telling LCD to receive data)

	wait_ms(1) ;

	MCAL_GPIO_WritePin(LCD_PORT, E, GPIO_PIN_RESET) ;
	//CLEAR_BIT (PORTC_REG , E) ;						// E is set low (telling LCD that we are done sending data)

	command = (LCD_PORT->ODR & 0x0F) | (cmd << 4);		// Sending lower nibble
	MCAL_GPIO_WritePort(LCD_PORT, command) ;
	//DIO_SetPortValue(portC , command) ;

	MCAL_GPIO_WritePin(LCD_PORT, Rs, GPIO_PIN_RESET) ;
	//CLEAR_BIT (PORTC_REG , Rs) ;					// write command

	MCAL_GPIO_WritePin(LCD_PORT, E, GPIO_PIN_SET) ;
	//SET_BIT (PORTC_REG , E) ;						//  E is set high (telling LCD to receive data)
	wait_ms(1) ;

	MCAL_GPIO_WritePin(LCD_PORT, E, GPIO_PIN_RESET) ;
	//CLEAR_BIT (PORTC_REG , E) ;						// E is set low (telling LCD that we are done sending data)
}

/*
Description : function to send character to LCD
inputs		: char data
outputs		: none
 */
void LCD_send_char (char value) {

	char sent_value ; 

	sent_value = (LCD_PORT->ODR & 0x0F) | (value & 0xF0);		/* Sending upper nibble */
	MCAL_GPIO_WritePort(LCD_PORT, sent_value) ;

	MCAL_GPIO_WritePin(LCD_PORT, Rs, GPIO_PIN_SET) ;
	MCAL_GPIO_WritePin(LCD_PORT, E, GPIO_PIN_SET) ;				//  E is set high (telling LCD to receive data)
	wait_ms(1) ;
	MCAL_GPIO_WritePin(LCD_PORT, E, GPIO_PIN_RESET) ;			// E is set low (telling LCD that we are done sending data)


	sent_value = (LCD_PORT->ODR & 0x0F) | (value << 4);		// Sending lower nibble
	MCAL_GPIO_WritePort(LCD_PORT, sent_value) ;

	MCAL_GPIO_WritePin(LCD_PORT, Rs, GPIO_PIN_SET) ;

	MCAL_GPIO_WritePin(LCD_PORT, E, GPIO_PIN_SET) ;			//  E is set high (telling LCD to receive data)
	wait_ms(1) ;
	MCAL_GPIO_WritePin(LCD_PORT, E, GPIO_PIN_RESET) ;		// E is set low (telling LCD that we are done sending data)

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
