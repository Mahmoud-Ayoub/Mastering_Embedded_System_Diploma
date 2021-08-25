#include "driver.h"
#include "pressure_sensor.h"
#include "PC_Algorithm.h"
#include "Alarm.h"

int main (){
	
	int p_value ; 
	extern int pressure_threshold ; 

	GPIO_INITIALIZATION();
	while (1)
	{
		p_value = getPressureVal() ; 
		if (p_value > pressure_threshold) {
			Alarm_ON () ; 
		}
		else if (p_value <= pressure_threshold) {
			Alarm_OFF () ; 
		}	
	}
}

