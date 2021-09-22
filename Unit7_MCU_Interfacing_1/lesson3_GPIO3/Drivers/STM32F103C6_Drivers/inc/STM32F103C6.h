/*
 * STM32F103C6.h
 *
 *      Author: Mahmoud Ayoub
 */

#ifndef INC_STM32F103C6_H_
#define INC_STM32F103C6_H_

// includes
#include "stdlib.h"
#include "stdint.h"
// ==================================================

//---------------------------------------------------------------------------------------------------

// Base addresses for memories
#define FLASH_MEMORY_BASE 						0x08000000UL
#define SYSTEM_MEMORY_BASE						0x1FFFF000UL
#define SRAM_BASE							0x20000000UL
#define PEREPHIRALS_BASE 						0x40000000UL
#define Cortex_M3_Internal_Peripherals_BASE 				0xE0000000UL
// ==================================================

//Base address of RCC
#define RCC_BASE 							0x40021000UL
// ==================================================

//Base address of GPIO
#define GPIOA_BASE 							0x40010800UL
#define GPIOB_BASE 							0x40010C00UL
#define GPIOC_BASE 							0x40011000UL
#define GPIOD_BASE 							0x40011400UL
#define GPIOE_BASE 							0x40011800UL
#define GPIOF_BASE 							0x40011C00UL
#define GPIOG_BASE 							0x40012000UL
// ==================================================

//Base address of AFIO
#define AFIO_BASE 							0x40010000UL
// ==================================================

//Base address of EXTI
#define EXTI_BASE 							0x40010400UL
// ==================================================

//---------------------------------------------------------------------------------------------------

// Peripheral Registers : RCC
typedef struct {
	volatile uint32_t CR ;
	volatile uint32_t CFGR ;
	volatile uint32_t CIR ;
	volatile uint32_t APB2RSTR ;
	volatile uint32_t APB1RSTR ;
	volatile uint32_t AHBENR ;
	volatile uint32_t APB2ENR ;
	volatile uint32_t APB1ENR ;
	volatile uint32_t BDCR ;
	volatile uint32_t CSR ;
}RCC_TypeDef;
// ==================================================

// Peripheral Registers : GPIO
typedef struct {
	volatile uint32_t CRL ;
	volatile uint32_t CRH ;
	volatile uint32_t IDR ;
	volatile uint32_t ODR ;
	volatile uint32_t BSRR ;
	volatile uint32_t BRR ;
	volatile uint32_t LCKR ;
}GPIO_TypeDef;
// ==================================================

// Peripheral Registers : AFIO
typedef struct {
	volatile uint32_t EVCR ;
	volatile uint32_t MAPR ;
	volatile uint32_t EXTICR1 ;
	volatile uint32_t EXTICR2 ;
	volatile uint32_t EXTICR3 ;
	volatile uint32_t EXTICR4 ;
	volatile uint32_t RESERVED ;
	volatile uint32_t MAPR2 ;
}AFIO_Typedef;
// ==================================================

// Peripheral Registers : EXTI
typedef struct {
	volatile uint32_t IMR ;
	volatile uint32_t EMR ;
	volatile uint32_t RTSR ;
	volatile uint32_t FTSR ;
	volatile uint32_t SWIER ;
	volatile uint32_t PR ;
}EXTI_TypeDef;
// ==================================================

//---------------------------------------------------------------------------------------------------

// Peripheral Instants
#define GPIOA 								((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB 								((GPIO_TypeDef*)GPIOB_BASE)
#define GPIOC 								((GPIO_TypeDef*)GPIOC_BASE)
#define GPIOD 								((GPIO_TypeDef*)GPIOD_BASE)
#define GPIOE 								((GPIO_TypeDef*)GPIOE_BASE)
#define GPIOF 								((GPIO_TypeDef*)GPIOF_BASE)
#define GPIOG 								((GPIO_TypeDef*)GPIOG_BASE)
#define RCC 								((RCC_TypeDef*)RCC_BASE)
// ==================================================

//---------------------------------------------------------------------------------------------------
// Clock Management MACROS
#define CLK_EN_GPIOA()							(RCC->APB2ENR |= (1 << 2))
#define CLK_EN_GPIOB()							(RCC->APB2ENR |= (1 << 3))
#define CLK_EN_GPIOC()							(RCC->APB2ENR |= (1 << 4))
#define CLK_EN_GPIOD()							(RCC->APB2ENR |= (1 << 5))
#define CLK_EN_GPIOE()							(RCC->APB2ENR |= (1 << 6))
#define CLK_EN_GPIOF()							(RCC->APB2ENR |= (1 << 7))
#define CLK_EN_GPIOG()							(RCC->APB2ENR |= (1 << 8))
// ==================================================

#endif /* INC_STM32F103C6_H_ */
