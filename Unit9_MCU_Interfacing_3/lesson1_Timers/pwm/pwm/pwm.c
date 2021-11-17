/*
 * pwm.c
 *
 *  Author: Mahmoud Ayoub
 */ 
#include "pwm.h"

/*
	@Fn		: MCAL_Pwm_Init
	@brief	: initialize timer 0 with the required PWM specifications 
	@inputs : pwm configuration
	@outputs : none
*/
void MCAL_Pwm_Init (PWM_Config_t* pwm_config) {
	T0_Control_REG |= (pwm_config->pwm_mode) | (pwm_config->output_compare_mode) | (pwm_config->clock_select) ; 
}

/*
	@Fn		: MCAL_Pwm_Start
	@brief	: Start generating pwm waveform on OC0 pin with the required duty cycle
	@inputs : duty cycle
	@outputs : none
*/
void MCAL_Pwm_Start (uint8 duty_cycle) {
	uint8 outcmp_value = 255 * duty_cycle / 100 ;
	T0_OutCmp_REG = outcmp_value ;
}
