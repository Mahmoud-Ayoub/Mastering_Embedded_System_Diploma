/*
 ******************************************************************************
 * @file           : main.c
 * @author         : Mahmoud Ayoub
 * @brief          : Toggle LED on STM32F103C6
 ******************************************************************************
 */

#include <stdint.h>
typedef volatile unsigned int vuint32_t ; 

#define RCC_APB2ENR 	*((vuint32_t*)(0x40021000+0x18))
#define GPIO_PA_CRH 	*((vuint32_t*)(0x40010800+0x04))
#define GPIO_PA_ODR 	*((vuint32_t*)(0x40010800+0x0C))

typedef union {
	vuint32_t all_port ;
	struct {
		vuint32_t reserved : 13 ;
		vuint32_t pin_13 : 1 ;
	}Pin;

}PA_ODR_t;
volatile PA_ODR_t* PA_ODR = (volatile PA_ODR_t*)(0x40010800+0x0C) ;   // pointer to output data register which is defined as union
int bss_var ; 
int main(void)
{

	RCC_APB2ENR |= (1<<2) ;
	GPIO_PA_CRH &= 0xFF0FFFFF ;
	GPIO_PA_CRH |= 0x00200000 ;

	int i = 0 ;
	while (1) {
		PA_ODR ->Pin.pin_13 = 1 ;
		for (i=0 ; i<10000 ; i++) ;
		PA_ODR ->Pin.pin_13 = 0 ;
		for (i=0 ; i<10000 ; i++) ;
	}
}