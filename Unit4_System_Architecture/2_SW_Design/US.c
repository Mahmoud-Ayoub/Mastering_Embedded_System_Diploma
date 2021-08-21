/*
 * US.c
 *      Author: Mahmoud Ayoub
 */
#include "US.h"
// define module variables
int distance = 0 ;

// global pointer to function
extern void (*US_p_state) () ;

int generate_random_distance (int low , int range , int count) {
	int i = 0 ;
	for (i=0 ; i<count ; i++) {
		int random_num = (rand() % (range-low+1)) + low ;
		return random_num ;
	}
}

void US_init (void) {
	// ultrasonic sensor init function definition
	printf ("UltraSonic sensor init \n") ;
}

// states' functions definition
STATE_define (US_busy) {
	// state name
	US_state_id = US_busy ;

	// state event
	distance = generate_random_distance(45 , 55 , 1) ;
	printf ("US_Busy State : distance = %d \n" , distance) ;
	US_distance(distance) ;
	US_p_state = STATE(US_busy) ;
}

