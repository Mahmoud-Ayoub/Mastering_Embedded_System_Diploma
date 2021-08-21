/*
 * main.c
 *      Author: Mahmoud Ayoub
 */
#include "state.h"
#include "US.h"
#include "CA.h"
#include "DC.h"

void setup () {
	// init all drivers
	// init all IRQ
	// init HAL
	// init BLOCK (if required) >> call init function inside block if implemented
	US_init() ;
	DC_init() ;
	printf ("==========================================") ;
	// Set state pointer for each BLOCK  (we have only one block in this project)
	US_p_state = STATE(US_busy) ;         // resolved by name of state function (base address)
	CA_p_state = STATE(CA_waiting) ;         // resolved by name of state function (base address)
	DC_p_state = STATE(DC_idle) ;         // resolved by name of state function (base address)
}

void main () {
	volatile int delay = 0 ;
	setup () ;
	while (1) {
		// call state pointer for each BLOCK
		US_p_state () ;
		CA_p_state () ;
		DC_p_state () ;
		for (delay = 0 ; delay < 1000 ; delay++) ;
	}
}


