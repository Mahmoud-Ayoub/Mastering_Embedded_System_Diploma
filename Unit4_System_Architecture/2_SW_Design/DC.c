/*
 * DC.c
 *      Author: Mahmoud Ayoub
 */
#include "DC.h"
// define module variables
int DC_speed = 0 ;

// global pointer to function
void (*DC_p_state) () ;

// DC motor init function definition
void DC_init (void) {
	printf ("DC motor init \n") ;
}

// states' functions definition
STATE_define (DC_idle) {
	// state name
	DC_state_id = DC_idle ;

	// state action
	DC_p_state = STATE(DC_idle) ;
	printf ("DC idle state : speed = %d \n" , DC_speed) ;
}

STATE_define (DC_busy) {
	// state name
	DC_state_id = DC_busy ;

	// state action
	DC_p_state = STATE(DC_idle) ;
	printf ("DC busy state : speed = %d \n" , DC_speed) ;
}
void DC_MOTOR_speed (int speed) {
	DC_speed = speed ;
	DC_p_state = STATE(DC_busy) ;
	printf ("CA -------- speed = %d --------- DC \n" , DC_speed) ;
}
