/*
 * FIFO.c
 *      Author: Mahmoud Ayoub
 */
#include "FIFO.h"

FIFO_Status FIFO_Init (FIFO_Buf_t* fifo , element_type* buffer , unsigned int length) {
	if (buffer == NULL)				// check buffer is initialized or not
		return FIFO_Null ;
	fifo -> length = length ;
	fifo -> count = 0 ;
	fifo -> base = buffer ;
	fifo -> head = buffer ;
	fifo -> tail = buffer ;
	return FIFO_no_error ;
}
FIFO_Status FIFO_Is_Full  (FIFO_Buf_t* fifo) {
	// check FIFO is valid or not
	if ( (fifo -> base == NULL) || (fifo -> head == NULL) || (fifo -> tail == NULL) ) {
		return FIFO_Null ;
	}
	if (fifo -> count == fifo -> length)
		return FIFO_full ;

	return FIFO_no_error ;
}

FIFO_Status FIFO_Enqueue (FIFO_Buf_t* fifo , element_type item) {
	// check FIFO is valid or not
	if ( (fifo -> base == NULL) || (fifo -> head == NULL) || (fifo -> tail == NULL) ) {
		return FIFO_Null ;
	}

	// check FIFO is full or not
	if (FIFO_Is_Full(fifo) == FIFO_full) {
		return FIFO_full ;
	}

	// Add item
	*(fifo -> head) = item ;
	fifo -> count ++ ;

	// circular buffer
	if (fifo -> head == (fifo -> base + (fifo -> length * sizeof (element_type)))) {     // head reached end of FIFO
		fifo -> head = fifo -> base ;
	}
	else
		fifo -> head ++ ;

	return FIFO_no_error ;
}
FIFO_Status FIFO_Dequeue  (FIFO_Buf_t* fifo , element_type* item) {
	// check FIFO is valid or not
	if ( (fifo -> base == NULL) || (fifo -> head == NULL) || (fifo -> tail == NULL) ) {
		return FIFO_Null ;
	}
	// check FIFO is empty or not
	if (fifo -> count == 0) {
		return FIFO_empty ;
	}
	*item = *(fifo -> tail) ;
	fifo -> count -- ;
	// circular buffer
	if (fifo -> tail == (fifo -> base + (fifo -> length * sizeof (element_type)))) {     // head reached end of FIFO
		fifo -> tail = fifo -> base ;
	}
	else
		fifo -> tail ++ ;

	return FIFO_no_error ;
}
void FIFO_Print  (FIFO_Buf_t* fifo) {
	int i ;
	element_type* temp = fifo->tail ;
	if (fifo->count == 0) {
		printf ("FIFO is Empty \n") ;
	}
	else {
		printf ("--------------	FIFO Print ------------------ \n") ;
		for (i=0 ; i<fifo->count ; i++) {
			printf ("Data in queue = %x \n" , *temp) ;
			temp ++ ;
		}
		printf ("-------------------------------- \n") ;
	}
}
