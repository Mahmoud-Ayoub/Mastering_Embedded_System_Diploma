#include "PC_Algorithm.h"
const int pressure_threshold = 20 ; 
const int delay_time = 10000 ; 
void Alarm_ON (void) {
	Set_Alarm_actuator(ALARM_ON) ; 
	Delay(delay_time) ; 
	Set_Alarm_actuator(ALARM_OFF) ; 
}
void Alarm_OFF (void) {
	Set_Alarm_actuator(ALARM_OFF) ;
}