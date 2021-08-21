/*
 * state.h
 *      Author: Mahmoud Ayoub
 */

#ifndef STATE_H_
#define STATE_H_

#define STATE_define(_stateFunc_) void ST_##_stateFunc_()
#define STATE(_stateFunc_) ST_##_stateFunc_

#include "stdio.h"
#include "stdlib.h"

// interfaces between modules (connections)
// to be visible from all modules
void US_distance (int distance) ;
void DC_MOTOR_speed (int speed) ;

#endif /* STATE_H_ */
