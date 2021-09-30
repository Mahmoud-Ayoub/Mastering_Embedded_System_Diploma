/*
 * Print_Message_on_LCD.c
 *
 * Author : Mahmoud Ayoub
 */ 

#include "./HAL/LCD/LCD.h"
int main(void)
{
	LCD_init() ; 
	LCD_send_str("Learn-In-Depth") ; 
	while (1) 
    {
		
    }
}

