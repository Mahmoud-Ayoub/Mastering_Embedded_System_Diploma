/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mahmoud Ayoub
 * @brief          : STM32F103C6
 ******************************************************************************
 */
#include "STM32F103C6.h"
#include "LCD.h"
#include "Keypad.h"
#include "EXTI.h"

void clock_init (void) {
	CLK_EN_GPIOA() ;
	CLK_EN_GPIOB() ;
	CLK_EN_AFIO() ;
}
void IRQ9_CB (void) {
	LCD_send_str("EXTI9 Happened") ;
	wait_ms(1000) ;
	LCD_clear() ;
}
int main(void)
{
	clock_init() ;
	LCD_init() ;


	EXTI_PinConfig_t EXTI_cfg ;
	EXTI_cfg.EXTI_Pin = EXTI9PB9 ;
	EXTI_cfg.Trigger =  EXTI_Trigger_RISING	;
	EXTI_cfg.P_IRQ_CallBack = IRQ9_CB ;
	EXTI_cfg.IRQ_EN = EXTI_IRQ_ENABLE ;
	MCAL_EXTI_Init(&EXTI_cfg) ;
	while (1) {

	}

}
