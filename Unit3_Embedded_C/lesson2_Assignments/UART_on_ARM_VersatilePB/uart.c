#include "uart.h"

void Uart_Send_String (unsigned char* P_tx_string) {
	while (*P_tx_string != '\0') {
		UART0DR = (unsigned int) *P_tx_string ; 
		P_tx_string ++ ; 
	}
}