/*
 * LIFO.h
 *      Author: Mahmoud Ayoub
 */

#ifndef LIFO_H_
#define LIFO_H_
#include "stdio.h"
#include "stdlib.h"

// LIFO Data Types
typedef struct {
	unsigned int length ;
	unsigned int count ;
	unsigned int* base ;
	unsigned int* head ;
}LIFO_Buf_t;

typedef enum {
	LIFO_no_error ,
	LIFO_full ,
	LIFO_empty ,
	LIFO_Null
}LIFO_Status;

// APIs
LIFO_Status LIFO_Init (LIFO_Buf_t* lifo , unsigned int* buffer , unsigned int length) ;
LIFO_Status LIFO_Push (LIFO_Buf_t* lifo , unsigned int item) ;
LIFO_Status LIFO_Pop  (LIFO_Buf_t* lifo , unsigned int* item) ;



#endif /* LIFO_H_ */
