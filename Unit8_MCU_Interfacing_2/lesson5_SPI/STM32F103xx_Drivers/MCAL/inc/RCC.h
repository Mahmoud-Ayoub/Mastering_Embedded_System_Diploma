/*
 * RCC.h
 *
 *      Author: Mahmoud Ayoub
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_

#include "STM32F103C6.h"

//---------------------------------------------------------------------------------------------------
// Clock Management MACROS
#define CLK_EN_GPIOA()							(RCC->APB2ENR |= (1 << 2))
#define CLK_EN_GPIOB()							(RCC->APB2ENR |= (1 << 3))
#define CLK_EN_GPIOC()							(RCC->APB2ENR |= (1 << 4))
#define CLK_EN_GPIOD()							(RCC->APB2ENR |= (1 << 5))
#define CLK_EN_GPIOE()							(RCC->APB2ENR |= (1 << 6))
#define CLK_EN_GPIOF()							(RCC->APB2ENR |= (1 << 7))
#define CLK_EN_GPIOG()							(RCC->APB2ENR |= (1 << 8))
#define CLK_EN_AFIO()							(RCC->APB2ENR |= (1 << 0))
#define CLK_EN_USART1()							(RCC->APB2ENR |= (1 << 14))
#define CLK_EN_USART2()							(RCC->APB1ENR |= (1 << 17))
#define CLK_EN_USART3()							(RCC->APB1ENR |= (1 << 18))
#define CLK_EN_SPI1()							(RCC->APB2ENR |= (1 << 12))
#define CLK_EN_SPI2()							(RCC->APB1ENR |= (1 << 14))

// ==================================================

//---------------------------------------------------------------------------------------------------
// RCC Reset
#define USART1_RESET()							(RCC->APB2RSTR |= (1<<14))
#define USART2_RESET()							(RCC->APB1RSTR |= (1<<17))
#define USART3_RESET()							(RCC->APB1RSTR |= (1<<18))
#define SPI1_RESET()							(RCC->APB2RSTR |= (1<<12))
#define SPI2_RESET()							(RCC->APB1RSTR |= (1<<14))

// ==================================================

//---------------------------------------------------------------------------------------------------
// Clock Sources
#define HSI_CLK 								((uint32_t)8000000)
#define HSE_CLK 								((uint32_t)16000000)
#define PLL_CLK									((uint32_t)16000000)
// ==================================================

//---------------------------------------------------------------------------------------------------
// APIs
uint32_t MCAL_RCC_Get_SysClk_Freq (void) ;
uint32_t MCAL_RCC_Get_HClk_Freq (void) ;
uint32_t MCAL_RCC_Get_PClk1_Freq (void) ;
uint32_t MCAL_RCC_Get_PClk2_Freq (void) ;


#endif /* INC_RCC_H_ */
