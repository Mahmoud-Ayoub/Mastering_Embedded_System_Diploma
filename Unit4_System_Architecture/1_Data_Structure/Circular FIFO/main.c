/*
 * main.c
 *      Author: Mahmoud Ayoub
 */
#include "FIFO.h"
#define width 5
element_type uart_buffer[width] ;
int main () {
	FIFO_Buf_t FIFO_uart ;
	element_type temp , i ;

	if (FIFO_Init(&FIFO_uart , uart_buffer , width) == FIFO_no_error) {
		printf ("FIFO initialization is DONE \n") ;
	}
	for (i=0 ; i<7 ; i++) {
		if (FIFO_Enqueue(&FIFO_uart , i) == FIFO_no_error) {
			printf ("FIFO Enqueue %x item ------DONE \n" , i) ;
		}
		else {
			printf ("FIFO Enqueue %x item ------Failed \n" , i) ;
		}
	}
	FIFO_Print(&FIFO_uart) ;

	if (FIFO_Dequeue(&FIFO_uart , &temp) == FIFO_no_error) {
		printf ("FIFO Dequeue %x item ------DONE \n" , temp) ;
	}
	if (FIFO_Dequeue(&FIFO_uart , &temp) == FIFO_no_error) {
		printf ("FIFO Dequeue %x item ------DONE \n" , temp) ;
	}
	FIFO_Print(&FIFO_uart) ;
	return 0 ;
}
