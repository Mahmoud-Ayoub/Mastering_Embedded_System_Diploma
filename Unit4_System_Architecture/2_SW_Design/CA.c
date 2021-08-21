/*
 * CA.c
 *      Author: Mahmoud Ayoub
 */
#include "CA.h"
// define module variables
int CA_speed = 0 ;
int CA_distance = 0 ;
int CA_threshold = 50 ;

// global pointer to function
void (*CA_p_state) () ;

// states' functions definition
STATE_define (CA_waiting) {
	// state name
	CA_state_id = CA_waiting ;
	printf ("CA_Waiting State : distance = %d	Speed = %d \n" , CA_distance , CA_speed) ;

	// state action
	CA_speed = 0 ;
	DC_MOTOR_speed(CA_speed) ;
}
STATE_define (CA_driving) {
	// state name
	CA_state_id = CA_driving ;
	printf ("CA_Driving State : distance = %d	Speed = %d \n" , CA_distance , CA_speed) ;

	// state action
	CA_speed = 70 ;
	DC_MOTOR_speed(CA_speed) ;
}

void US_distance (int distance) {         // connection definition in target (destination)
	CA_distance = distance ;
	( CA_distance <= CA_threshold ) ? (CA_p_state = STATE(CA_waiting)) : (CA_p_state = STATE(CA_driving)) ;
	printf ("US -------- distance = %d --------- CA \n" , CA_distance) ;
}
