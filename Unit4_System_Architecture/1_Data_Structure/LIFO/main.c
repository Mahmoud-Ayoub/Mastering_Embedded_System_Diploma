/*
 * main.c
 *      Author: Mahmoud Ayoub
 */

#include "LIFO.h"

unsigned int buffer1 [5] ;        // stored in .data section

int main () {
	int i , temp = 0 ;
	LIFO_Buf_t uart_lifo , I2C_lifo ;
	LIFO_Init(&uart_lifo , buffer1 , 5) ;              // Static
	unsigned int* buffer2 = (unsigned int*) malloc (5*sizeof(int)) ;    // stored in .heap section
	LIFO_Init(&I2C_lifo , buffer2 , 5) ;              // Dynamic

	for (i=0 ; i<5 ; i++) {
		if (LIFO_Push(&uart_lifo,i) == LIFO_no_error)
			printf ("UART LIFO add %d in buffer \n" , i) ;
	}
	printf ("\n") ;
	for (i=0 ; i<5 ; i++) {
		if (LIFO_Pop(&uart_lifo , &temp) == LIFO_no_error)
			printf ("UART LIFO get %d from buffer \n" , temp) ;
	}


	return 0 ;
}
