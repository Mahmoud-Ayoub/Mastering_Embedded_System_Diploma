/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mahmoud Ayoub
 * @brief          : Control LEDs using push buttons on STM32F103C6
 ******************************************************************************
 */

#include "Platform_Types.h"
#define GPIOA_BASE 0x40010800
#define GPIO_PA_CRL     *((vuint32_t*)(GPIOA_BASE+0x00))
#define GPIO_PA_CRH 	*((vuint32_t*)(GPIOA_BASE+0x04))
#define GPIO_PA_IDR 	*((vuint32_t*)(GPIOA_BASE+0x08))
#define GPIO_PA_ODR 	*((vuint32_t*)(GPIOA_BASE+0x0C))

#define GPIOB_BASE 0x40010C00
#define GPIO_PB_CRL     *((vuint32_t*)(GPIOB_BASE+0x00))
#define GPIO_PB_CRH 	*((vuint32_t*)(GPIOB_BASE+0x04))
#define GPIO_PB_IDR 	*((vuint32_t*)(GPIOB_BASE+0x08))
#define GPIO_PB_ODR 	*((vuint32_t*)(GPIOB_BASE+0x0C))


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


void clock_init (void) {
	RCC->RCC_APB2ENR |= (1 << 2) ;      // enable clock for PORT A
	RCC->RCC_APB2ENR |= (1 << 3) ;      // enable clock for PORT B
}
void GPIO_init (void) {
	// configure PA1 as input floating
	GPIO_PA_CRL |= (0b0100 << 4) ;

	// configure PA13 as input floating
	GPIO_PA_CRH |= (0b0100 << 20) ;

	// configure PB1 as output push-pull
	GPIO_PB_CRL &= ~(0b1111 << 4) ;       // clear all 4 mode and config bits
	GPIO_PB_CRL |= (0b0001 << 4) ;

	// configure PB13 as output push-pull
	GPIO_PB_CRH &= ~(0b1111 << 20) ;       // clear all 4 mode and config bits
	GPIO_PB_CRH |= (0b0001 << 20) ;

}
int main(void)
{
	clock_init() ;
	GPIO_init() ;

	int delay = 0 ;
	GPIO_PB_ODR |= (1 << 1) ;            // LED 1 initially OFF
	GPIO_PB_ODR |= (1 << 13) ;			 // LED 2 initially OFF

	while (1) {
		if (((GPIO_PA_IDR & (1<<1)) >> 1) == 0) {
			GPIO_PB_ODR ^= (1 << 1) ;         // Toggle LED on PB1
			while (((GPIO_PA_IDR & (1<<1)) >> 1) == 0) ;
		}


		if (((GPIO_PA_IDR & (1<<13)) >> 13) == 1) {
			GPIO_PB_ODR ^= (1 << 13) ;         // Toggle LED on PB13
			for (delay = 0 ; delay < 10000 ; delay ++) ;
		}
	}
}
