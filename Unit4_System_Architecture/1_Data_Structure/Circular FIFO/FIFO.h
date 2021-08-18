/*
 * FIFO.h
 *      Author: Mahmoud Ayoub
 */

#ifndef FIFO_H_
#define FIFO_H_
#include "stdio.h"
#include "stdint.h"

// select element type (uint8_t , uint16_t , uint32_t , ...)
#define element_type uint8_t

//FIFO Data types
typedef struct {
	unsigned int length ;
	unsigned int count ;
	element_type* base ;
	element_type* head ;
	element_type* tail ;
}FIFO_Buf_t;

typedef enum {
	FIFO_no_error ,
	FIFO_full ,
	FIFO_empty ,
	FIFO_Null
}FIFO_Status;

// APIs
FIFO_Status FIFO_Init (FIFO_Buf_t* fifo , element_type* buffer , unsigned int length) ;
FIFO_Status FIFO_Enqueue (FIFO_Buf_t* fifo , element_type item) ;
FIFO_Status FIFO_Dequeue  (FIFO_Buf_t* fifo , element_type* item) ;
FIFO_Status FIFO_Is_Full  (FIFO_Buf_t* fifo) ;
void FIFO_Print  (FIFO_Buf_t* fifo) ;

#endif /* FIFO_H_ */
