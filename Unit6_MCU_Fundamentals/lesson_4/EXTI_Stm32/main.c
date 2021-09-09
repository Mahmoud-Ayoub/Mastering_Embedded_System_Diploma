/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mahmoud Ayoub
 * @brief          : External interrupt  on STM32F103C6
 ******************************************************************************
 */

#include "Platform_Types.h"

#define GPIO_PA_CRL     *((vuint32_t*)(0x40010800+0x00))
#define GPIO_PA_CRH 	*((vuint32_t*)(0x40010800+0x04))
#define GPIO_PA_ODR 	*((vuint32_t*)(0x40010800+0x0C))
#define AFIO_EXTICR1 	*((vuint32_t*)(0x40010000+0x08))
#define NVIC_ISER0		*((vuint32_t*)(0xE000E100))

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

typedef struct {
	vuint32_t EXTI_IMR ;
	vuint32_t EXTI_EMR ;
	vuint32_t EXTI_RTSR ;
	vuint32_t EXTI_FTSR ;
	vuint32_t EXTI_SWIER ;
	vuint32_t EXTI_PR ;

}EXTINT_Typedef;
#define EXTI ((EXTINT_Typedef*)0x40010400)

typedef union {
	vuint32_t all_port ;
	struct {
		vuint32_t reserved : 13 ;
		vuint32_t pin_13 : 1 ;
	}Pin;

}PA_ODR_t;
volatile PA_ODR_t* PA_ODR = (volatile PA_ODR_t*)(0x40010800+0x0C) ;

void clock_init (void) {
	RCC->RCC_APB2ENR |= (1 << 0) ;      // enable clock for AFIO
	RCC->RCC_APB2ENR |= (1 << 2) ;      // enable clock for PORT A
}
void GPIO_init (void) {
	GPIO_PA_CRL |= (1 << 2) ;            // configure pin 0 in PORT A as input
	GPIO_PA_CRH &= 0xFF0FFFFF ;          // configure pin 13 in PORT A as output
	GPIO_PA_CRH |= 0x00200000 ;
}
int main(void)
{
	clock_init() ;
	GPIO_init() ;
	// configure alternative function for PA0
	AFIO_EXTICR1 = 0x0 ;

	// Rising trigger enabled
	EXTI->EXTI_RTSR |= (1 << 0) ;

	// Enable Interrupt mask
	EXTI->EXTI_IMR |= (1 << 0) ;

	// Enable NVIC INTREQ no 6
	NVIC_ISER0 |= (1 << 6) ;

	while (1) ;
}
void EXTI0_IRQHandler (void) {
	// Toggle LED on PA pin 13
	GPIO_PA_ODR ^= (1 << 13) ;
	// clear EXTI0 pending request
	EXTI->EXTI_PR |= (1 << 0) ;
}
