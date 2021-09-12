/*
 * Toggle_LEDs_Assignment.c
 *
 * Author : Mahmoud Ayoub
 */ 

#include "DIO_Config.h"
#include <util/delay.h>

void LED_init (void) {
	DIO_SetPinDirection(portD , 5 , OUTPUT) ;          // LED 1
	DIO_SetPinDirection(portD , 6 , OUTPUT) ;		   // LED 2
	DIO_SetPinDirection(portD , 7 , OUTPUT) ;		   // LED 3
	
	DIO_SetPinValue(portD , 5 , LOW) ;                // OFF initially
	DIO_SetPinValue(portD , 6 , LOW) ;
	DIO_SetPinValue(portD , 7 , LOW) ;	
}
void LEDs_OFF (void) {
	DIO_SetPinValue(portD , 5 , LOW) ;                // OFF 
	DIO_SetPinValue(portD , 6 , LOW) ;
	DIO_SetPinValue(portD , 7 , LOW) ;
}
void Buzzer_init (void) {
	DIO_SetPinDirection(portD , 4 , OUTPUT) ;          // buzzer
	DIO_SetPinValue(portD , 4 , LOW) ;                 // OFF initially
}
void Buzzer_Toggle (void) {
	DIO_SetPinValue(portD , 4 , HIGH) ;   // buzzer ON
	_delay_ms(1000) ;
	DIO_SetPinValue(portD , 4 , LOW) ;    // buzzer OFF
}


int main(void)
{
	LED_init() ; 
	Buzzer_init() ; 
    int i = 5 ; 
    while (1) 
    {
		LEDs_OFF() ; 
		DIO_SetPinValue(portD , i , HIGH) ; 
		_delay_ms(1000) ; 
		i ++ ; 
		if (i==8) {
			LEDs_OFF() ; 
			Buzzer_Toggle() ; 
			i = 5 ; 
		}
    }
}

