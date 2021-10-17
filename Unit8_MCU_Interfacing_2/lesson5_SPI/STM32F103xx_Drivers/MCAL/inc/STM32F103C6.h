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
#define SRAM_BASE								0x20000000UL
#define PEREPHIRALS_BASE 						0x40000000UL
#define Cortex_M3_Internal_Peripherals_BASE 	0xE0000000UL
#define NVIC_BASE								0xE000E100UL

// NVIC Registers
#define NVIC_ISER0								(*((volatile uint32_t *)(NVIC_BASE+0x000)))
#define NVIC_ISER1								(*((volatile uint32_t *)(NVIC_BASE+0x004)))
#define NVIC_ISER2								(*((volatile uint32_t *)(NVIC_BASE+0x008)))
#define NVIC_ICER0								(*((volatile uint32_t *)(NVIC_BASE+0x080)))
#define NVIC_ICER1								(*((volatile uint32_t *)(NVIC_BASE+0x084)))
#define NVIC_ICER2								(*((volatile uint32_t *)(NVIC_BASE+0x088)))
#define NVIC_ISPR0								(*((volatile uint32_t *)(NVIC_BASE+0x100)))
#define NVIC_ISPR1								(*((volatile uint32_t *)(NVIC_BASE+0x104)))
#define NVIC_ISPR2								(*((volatile uint32_t *)(NVIC_BASE+0x108)))
#define NVIC_ICPR0								(*((volatile uint32_t *)(NVIC_BASE+0x180)))
#define NVIC_ICPR1								(*((volatile uint32_t *)(NVIC_BASE+0x184)))
#define NVIC_ICPR2								(*((volatile uint32_t *)(NVIC_BASE+0x188)))
#define NVIC_IABR0								(*((volatile uint32_t *)(NVIC_BASE+0x200)))
// ==================================================

//Base address of RCC
#define RCC_BASE 								0x40021000UL
// ==================================================

//Base address of GPIO
#define GPIOA_BASE 								0x40010800UL
#define GPIOB_BASE 								0x40010C00UL
#define GPIOC_BASE 								0x40011000UL
#define GPIOD_BASE 								0x40011400UL
#define GPIOE_BASE 								0x40011800UL
#define GPIOF_BASE 								0x40011C00UL
#define GPIOG_BASE 								0x40012000UL
// ==================================================

//Base address of AFIO
#define AFIO_BASE 								0x40010000UL
// ==================================================

//Base address of EXTI
#define EXTI_BASE 								0x40010400UL
// ==================================================

// Base address of USART
#define USART1_BASE								0x40013800UL
#define USART2_BASE								0x40004400UL
#define USART3_BASE								0x40004800UL
// ==================================================

//Base address of SPI
#define SPI1_BASE 								0x40013000UL
#define SPI2_BASE 								0x40003800UL

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
	volatile uint32_t EXTICR[4] ;
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

// Peripheral Registers : USART
typedef struct {
	volatile uint32_t SR ;
	volatile uint32_t DR ;
	volatile uint32_t BRR ;
	volatile uint32_t CR1 ;
	volatile uint32_t CR2 ;
	volatile uint32_t CR3 ;
	volatile uint32_t GTPR ;
}USART_TypeDef;
// ==================================================

// Peripheral Registers : SPI
typedef struct {
	volatile uint32_t CR1 ;
	volatile uint32_t CR2 ;
	volatile uint32_t SR ;
	volatile uint32_t DR ;
	volatile uint32_t CRCPR ;
	volatile uint32_t RXCRCR ;
	volatile uint32_t TXCRCR ;
	volatile uint32_t I2SCFGR ;
	volatile uint32_t I2SPR ;
}SPI_TypeDef;
// ==================================================

//---------------------------------------------------------------------------------------------------

// Peripheral Instants
#define GPIOA 									((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB 									((GPIO_TypeDef*)GPIOB_BASE)
#define GPIOC 									((GPIO_TypeDef*)GPIOC_BASE)
#define GPIOD 									((GPIO_TypeDef*)GPIOD_BASE)
#define GPIOE 									((GPIO_TypeDef*)GPIOE_BASE)
#define GPIOF 									((GPIO_TypeDef*)GPIOF_BASE)
#define GPIOG 									((GPIO_TypeDef*)GPIOG_BASE)

#define RCC 									((RCC_TypeDef*)RCC_BASE)

#define AFIO									((AFIO_Typedef*)AFIO_BASE)

#define EXTI									((EXTI_TypeDef*)EXTI_BASE)

#define USART1									((USART_TypeDef*)USART1_BASE)
#define USART2									((USART_TypeDef*)USART2_BASE)
#define USART3									((USART_TypeDef*)USART3_BASE)

#define SPI1									((SPI_TypeDef*)SPI1_BASE)
#define SPI2									((SPI_TypeDef*)SPI2_BASE)

// ==================================================

//---------------------------------------------------------------------------------------------------
// IVT
// @ref IVT_IRQ_Number
#define EXTI0_IRQ	6
#define EXTI1_IRQ	7
#define EXTI2_IRQ	8
#define EXTI3_IRQ	9
#define EXTI4_IRQ	10
#define EXTI5_IRQ	23
#define EXTI6_IRQ	23
#define EXTI7_IRQ	23
#define EXTI8_IRQ	23
#define EXTI9_IRQ	23
#define EXTI10_IRQ	40
#define EXTI11_IRQ	40
#define EXTI12_IRQ	40
#define EXTI13_IRQ	40
#define EXTI14_IRQ	40
#define EXTI15_IRQ	40
#define USART1_IRQ	37
#define USART2_IRQ	38
#define USART3_IRQ	39
#define SPI1_IRQ	35
#define SPI2_IRQ	36



//---------------------------------------------------------------------------------------------------
// NVIC_IRQ Enable / Disable
#define NVIC_IRQ6_EXTI0_ENABLE()		(NVIC_ISER0 |= (1<<6))
#define NVIC_IRQ7_EXTI1_ENABLE()		(NVIC_ISER0 |= (1<<7))
#define NVIC_IRQ8_EXTI2_ENABLE()		(NVIC_ISER0 |= (1<<8))
#define NVIC_IRQ9_EXTI3_ENABLE()		(NVIC_ISER0 |= (1<<9))
#define NVIC_IRQ10_EXTI4_ENABLE()		(NVIC_ISER0 |= (1<<10))
#define NVIC_IRQ23_EXTI5_9_ENABLE()		(NVIC_ISER0 |= (1<<23))
#define NVIC_IRQ40_EXTI10_15_ENABLE()	(NVIC_ISER1 |= (1<<8))		// 40 - 32 = 8
#define NVIC_IRQ37_USART1_ENABLE()		(NVIC_ISER1 |= (1<<5))		// 37 - 32 = 5
#define NVIC_IRQ38_USART2_ENABLE()		(NVIC_ISER1 |= (1<<6))		// 38 - 32 = 6
#define NVIC_IRQ39_USART3_ENABLE()		(NVIC_ISER1 |= (1<<7))		// 39 - 32 = 7
#define NVIC_IRQ35_SPI1_ENABLE()		(NVIC_ISER1 |= (1<<3))		// 35 - 32 = 3
#define NVIC_IRQ36_SPI2_ENABLE()		(NVIC_ISER1 |= (1<<4))		// 36 - 32 = 4


#define NVIC_IRQ6_EXTI0_DISABLE()		(NVIC_ICER0 |= (1<<6))
#define NVIC_IRQ7_EXTI1_DISABLE()		(NVIC_ICER0 |= (1<<7))
#define NVIC_IRQ8_EXTI2_DISABLE()		(NVIC_ICER0 |= (1<<8))
#define NVIC_IRQ9_EXTI3_DISABLE()		(NVIC_ICER0 |= (1<<9))
#define NVIC_IRQ10_EXTI4_DISABLE()		(NVIC_ICER0 |= (1<<10))
#define NVIC_IRQ23_EXTI5_9_DISABLE()	(NVIC_ICER0 |= (1<<23))
#define NVIC_IRQ40_EXTI10_15_DISABLE()	(NVIC_ICER1 |= (1<<8))		// 40 - 32 = 8
#define NVIC_IRQ37_USART1_DISABLE()		(NVIC_ICER1 |= (1<<5))		// 37 - 32 = 5
#define NVIC_IRQ38_USART2_DISABLE()		(NVIC_ICER1 |= (1<<6))		// 38 - 32 = 6
#define NVIC_IRQ39_USART3_DISABLE()		(NVIC_ICER1 |= (1<<7))		// 39 - 32 = 7
#define NVIC_IRQ35_SPI1_DISABLE()		(NVIC_ICER1 |= (1<<3))		// 35 - 32 = 3
#define NVIC_IRQ36_SPI2_DISABLE()		(NVIC_ICER1 |= (1<<4))		// 36 - 32 = 4


#endif /* INC_STM32F103C6_H_ */
