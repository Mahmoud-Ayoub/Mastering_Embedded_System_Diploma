/*
 * pwm.c
 *
 * Author : Mahmoud Ayoub
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "pwm.h"

#define F_CPU 8000000UL

void main()
{
	
	DDRB |= (1<<PB3);
	PWM_Config_t pwm0_cfg ; 
	pwm0_cfg.pwm_mode = PWM_MODE_PHASE_CORRECT ; 
	pwm0_cfg.output_compare_mode = PWM_OUTCMP_MODE_FAST_INVERTING ; 
	pwm0_cfg.clock_select = PWM_CLK_INTERNAL_8 ;
	MCAL_Pwm_Init(&pwm0_cfg) ; 
	 
	while(1)
	{
		MCAL_Pwm_Start(80);   
	}

}
