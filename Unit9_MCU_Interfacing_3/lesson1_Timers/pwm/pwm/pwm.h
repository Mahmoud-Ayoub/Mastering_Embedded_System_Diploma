/*
 * pwm.h
 *
 *  Author: Mahmoud Ayoub
 */ 


#ifndef PWM_H_
#define PWM_H_
#include "Std_Types.h"

#define T0_Control_REG			(*((volatile uint8*)0x53))
#define T0_Data_REG				(*((volatile uint8*)0x52))
#define T0_OutCmp_REG			(*((volatile uint8*)0x5C))
#define T0_INTMask_REG			(*((volatile uint8*)0x59))
#define T0_Status_REG			(*((volatile uint8*)0x58))

/*
#define NON_INVERTING_MODE 0
#define INVERTING_MODE 1
*/

typedef struct {
	// specifies PWM mode required (fast pwm , phase correct pwm)
	// This parameter is set using @ref PWM_MODE @ pwm.h
	uint8 pwm_mode ;
	
	// specifies PWM output compare mode (inverting , non-inverting)
	// This parameter is set using @ref PWM_OUTCMP_MODE @ pwm.h
	uint8 output_compare_mode ; 
	
	// specifies clock source to be used (no clock , internal with prescaler , external)
	// This parameter is set using @ref PWM_CLK @ pwm.h
	uint8 clock_select ; 
	
}PWM_Config_t;

/**************************************************************
						Reference Macros
***************************************************************/
// @ref PWM_MODE
#define PWM_MODE_FAST			((uint8)( (1<<3) | (1<<6)))
#define PWM_MODE_PHASE_CORRECT	((uint8)((0<<3) | (1<<6)))	

// @ref PWM_OUTCMP_MODE
#define PWM_OUTCMP_MODE_FAST_INVERTING		((uint8)((1<<5) | (1<<4)))
#define PWM_OUTCMP_MODE_FAST_NON_INVERTING	((uint8)((1<<5) | (0<<4)))
#define PWM_OUTCMP_MODE_PHASE_SET_ON_CMP	((uint8)((1<<5) | (1<<4)))
#define PWM_OUTCMP_MODE_PHASE_CLEAR_ON_CMP	((uint8)((1<<5) | (0<<4)))

// @ref PWM_CLK
#define PWM_CLK_NO_SRC				((uint8)(0b000 << 0))
#define PWM_CLK_INTERNAL_1			((uint8)(0b001 << 0))
#define PWM_CLK_INTERNAL_8			((uint8)(0b010 << 0))
#define PWM_CLK_INTERNAL_64			((uint8)(0b011 << 0))
#define PWM_CLK_INTERNAL_256		((uint8)(0b100 << 0))
#define PWM_CLK_INTERNAL_1024		((uint8)(0b101 << 0))
#define PWM_CLK_EXTERNAL_FALLING	((uint8)(0b110 << 0))
#define PWM_CLK_EXTERNAL_RISING		((uint8)(0b111 << 0))

/**************************************************************
						APIs
***************************************************************/
void MCAL_Pwm_Init (PWM_Config_t* pwm_config) ; 
void MCAL_Pwm_Start (uint8 duty_cycle) ; 

#endif /* PWM_H_ */