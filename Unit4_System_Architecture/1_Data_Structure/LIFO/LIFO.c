/*
 * LIFO.c
 *      Author: Mahmoud Ayoub
 */
#include "LIFO.h"

LIFO_Status LIFO_Init (LIFO_Buf_t* lifo , unsigned int* buffer , unsigned int length)  {
	if (buffer == NULL) {          // check buffer is initialized or not
		return LIFO_Null ;
	}
	lifo -> base = buffer ;
	lifo -> head = buffer ;
	lifo -> length = length ;
	lifo -> count = 0 ;
	return LIFO_no_error ;
}
LIFO_Status LIFO_Push (LIFO_Buf_t* lifo , unsigned int item) {
	// check LIFO is valid or not
	if ( (lifo -> base == NULL) || (lifo -> head == NULL) ) {
		return LIFO_Null ;
	}

	// check LIFO is full or not
	if (lifo -> count == lifo -> length) {
		return LIFO_full ;
	}

	// Add item
	*(lifo -> head) = item ;
	lifo -> head ++ ;
	lifo -> count ++ ;
	return LIFO_no_error ;
}

LIFO_Status LIFO_Pop  (LIFO_Buf_t* lifo , unsigned int* item) {
	// check LIFO is valid or not
	if ( (lifo -> base == NULL) || (lifo -> head == NULL) ) {
		return LIFO_Null ;
	}

	// check lifo is empty or not
	if (lifo -> count == 0) {
		return LIFO_empty ;
	}
	lifo -> head -- ;
	*item = *(lifo -> head) ;
	lifo -> count -- ;
	return LIFO_no_error ;
}

