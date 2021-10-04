/*
 * UART.h
 *
 *  Author: Mahmoud Ayoub
 */ 


#ifndef UART_H_
#define UART_H_

// UART Registers
#define UART_UDR		(*((volatile unsigned char*)0x2C))
#define UART_UCSRA		(*((volatile unsigned char*)0x2B))
#define UART_UCSRB		(*((volatile unsigned char*)0x2A))
#define UART_UCSRC		(*((volatile unsigned char*)0x40))
#define UART_UBRRH		(*((volatile unsigned char*)0x40))
#define UART_UBRRL		(*((volatile unsigned char*)0x29))

// Flags
#define RXEN	4
#define TXEN	3
#define UDRE	5
#define RXC		7

#define F_CPU 8000000UL			/* Define frequency here its 8MHz */

typedef enum {
	_1_BIT , 
	_2_BITS , 	
}EN_STOP_BITS ;

typedef enum {
	_5_BITS ,
	_6_BITS ,
	_7_BITS ,
	_8_BITS ,
}EN_DATA_SIZE;

void UART_init (unsigned int baud_rate , EN_STOP_BITS stop_bits , EN_DATA_SIZE data_size) ; 
void UART_Transmit_Char (unsigned char data) ; 
void UART_Transmit_String (char* str) ; 
unsigned char UART_Receive_Char (void) ; 
char* UART_Receive_String (void) ; 

#endif /* UART_H_ */