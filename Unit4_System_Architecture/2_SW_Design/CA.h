/*
 * CA.h
 *      Author: Mahmoud Ayoub
 */

#ifndef CA_H_
#define CA_H_
#include "state.h"

// Define States
enum {
	CA_waiting ,
	CA_driving
} CA_state_id;

// prototypes of states declarations
STATE_define(CA_waiting) ;
STATE_define(CA_driving) ;

// global pointer to function
extern void (*CA_p_state) () ;


#endif /* CA_H_ */
