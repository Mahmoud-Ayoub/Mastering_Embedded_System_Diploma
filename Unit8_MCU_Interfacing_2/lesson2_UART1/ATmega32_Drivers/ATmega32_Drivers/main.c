/*
 * ATmega32_Drivers.c
 *
 * Author : Mahmoud Ayoub
 */ 

#include "./MCAL/UART/UART.h"
#include "./HAL/LCD/LCD.h"

int main()
{
	char* data_str  ;
	unsigned char counter = 0 ;
	
	LCD_init() ;
	UART_init(9600 , _1_BIT , _8_BITS) ;
	while (1) {
		data_str = UART_Receive_String() ;
		LCD_send_str(data_str) ;
	}
}

