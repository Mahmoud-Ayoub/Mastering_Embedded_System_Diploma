#include "uart.h"

unsigned char string_buffer [50] = "learn-in-depth:Mahmoud" ; 
void main (void) {
	Uart_Send_String (string_buffer) ; 
}