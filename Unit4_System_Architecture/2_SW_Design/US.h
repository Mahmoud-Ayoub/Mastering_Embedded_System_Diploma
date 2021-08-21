/*
 * US.h
 *      Author: Mahmoud Ayoub
 */

#ifndef US_H_
#define US_H_

#include "state.h"

// Define States
enum {
	US_busy
} US_state_id;

// prototypes of states declarations
STATE_define(US_busy) ;

// ultrasonic sensor init function prototype
void US_init (void) ;

// global pointer to function
void (*US_p_state) () ;


#endif /* US_H_ */
