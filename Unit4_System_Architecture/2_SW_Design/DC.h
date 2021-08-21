/*
 * DC.h
 *      Author: Mahmoud Ayoub
 */

#ifndef DC_H_
#define DC_H_

#include "state.h"

// Define States
enum {
	DC_idle ,
	DC_busy
} DC_state_id;

// prototypes of states declarations
STATE_define(DC_idle) ;
STATE_define(DC_busy) ;

// DC motor init function prototype
void DC_init (void) ;

// global pointer to function
extern void (*DC_p_state) () ;


#endif /* DC_H_ */
