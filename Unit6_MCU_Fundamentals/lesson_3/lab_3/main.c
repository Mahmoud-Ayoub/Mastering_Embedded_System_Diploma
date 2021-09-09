/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mahmoud Ayoub
 * @brief          : Toggle LED on STM32F103C6
 ******************************************************************************
 */

#include "Platform_Types.h"
#define GPIO_PA_CRH 	*((vuint32_t*)(0x40010800+0x04))
#define GPIO_PA_ODR 	*((vuint32_t*)(0x40010800+0x0C))

typedef struct {
	vuint32_t RCC_CR ;
	vuint32_t RCC_CFGR ;
	vuint32_t RCC_CIR ;
	vuint32_t RCC_APB2RSTR ;
	vuint32_t RCC_APB1RSTR ;
	vuint32_t RCC_AHBENR ;
	vuint32_t RCC_APB2ENR ;
	vuint32_t RCC_APB1ENR ;
	vuint32_t RCC_BDCR ;
	vuint32_t RCC_CSR ;
}RCC_Typedef;
#define RCC ((RCC_Typedef*)0x40021000)

typedef union {
	vuint32_t all_port ;
	struct {
		vuint32_t reserved : 13 ;
		vuint32_t pin_13 : 1 ;
	}Pin;

}PA_ODR_t;

volatile PA_ODR_t* PA_ODR = (volatile PA_ODR_t*)(0x40010800+0x0C) ;

void clock_init (void) {
	/*
	 * APB1 	>> 16 MHz
	 * APB2 	>> 8  MHz
	 * AHB  	>> 32 MHz
	 * SysClk  	>> 32 MHz
	 *
	 */

	RCC->RCC_CFGR |= (0b0110 << 18) ;      // PLL multiplier = 8
	RCC->RCC_CFGR |= (0b101 << 11) ;       // APB2 prescaler = 4
	RCC->RCC_CFGR |= (0b100 << 8) ;        // APB1 prescaler = 2
	RCC->RCC_CFGR |= (0b10 << 0) ;         // PLL selected as system clock
	RCC->RCC_CR |= (1 << 24) ;             // PLL enable
	RCC->RCC_APB2ENR |= (1 << 2) ;
}

int main(void)
{
	clock_init() ;
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
