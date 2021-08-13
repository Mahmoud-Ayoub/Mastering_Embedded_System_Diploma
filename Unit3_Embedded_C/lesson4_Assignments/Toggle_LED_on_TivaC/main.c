/*
 ******************************************************************************
 * @file           : main.c
 * @author         : Mahmoud Ayoub
 * @brief          : Toggle LED on TivaC
 ******************************************************************************
 */

#include <stdint.h>
typedef volatile unsigned int vuint32_t ; 

#define SYSCTL_RCGC2_R 		*((vuint32_t*)(0x400FE000+0x108))
#define GPIO_PORTF_DATA_R 	*((vuint32_t*)(0x40025000+0x3FC))
#define GPIO_PORTF_DIR_R 	*((vuint32_t*)(0x40025000+0x400))
#define GPIO_PORTF_DEN_R 	*((vuint32_t*)(0x40025000+0x51C))
 
int main(void)
{
	vuint32_t i = 0 ;
	SYSCTL_RCGC2_R = 0x00000020 ; 
	for (i=0 ; i<200 ; i++) ;     /* Delay to make sure that GPIOF is up and running */
	GPIO_PORTF_DIR_R |= (1<<3) ; 
	GPIO_PORTF_DEN_R |= (1<<3) ; 
	
	while (1) {
		GPIO_PORTF_DATA_R |= (1<<3) ;
		for (i=0 ; i<100000 ; i++) ; 
		GPIO_PORTF_DATA_R &= ~(1<<3) ;
		for (i=0 ; i<100000 ; i++) ; 
	}

	return 0 ;
}