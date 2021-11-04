/*
 * EXTI.c
 *
 *      Author: Mahmoud Ayoub
 */

#include "EXTI.h"

void (*GP_IRQ_CallBack[15])(void) ;

#define AFIO_GPIO_EXTI_MAPPING(x)	((x == GPIOA)?0:\
									(x == GPIOB)?1:\
									(x == GPIOC)?2:\
									(x == GPIOD)?3:0)

void NVIC_Enable (uint16_t IRQ) {
	switch (IRQ) {
	case 0 :
		NVIC_IRQ6_EXTI0_ENABLE() ;
		break ;

	case 1 :
		NVIC_IRQ7_EXTI1_ENABLE() ;
		break ;

	case 2 :
		NVIC_IRQ8_EXTI2_ENABLE() ;
		break ;

	case 3 :
		NVIC_IRQ9_EXTI3_ENABLE() ;
		break ;

	case 4 :
		NVIC_IRQ10_EXTI4_ENABLE() ;
		break ;

	case 5 :
	case 6 :
	case 7 :
	case 8 :
	case 9 :
		NVIC_IRQ23_EXTI5_9_ENABLE() ;
		break ;

	case 10 :
	case 11 :
	case 12 :
	case 13 :
	case 14 :
	case 15 :
		NVIC_IRQ40_EXTI10_15_ENABLE() ;
		break ;
	}
}

void NVIC_Disable (uint16_t IRQ) {
	switch (IRQ) {
	case 0 :
		NVIC_IRQ6_EXTI0_DISABLE() ;
		break ;

	case 1 :
		NVIC_IRQ7_EXTI1_DISABLE() ;
		break ;

	case 2 :
		NVIC_IRQ8_EXTI2_DISABLE() ;
		break ;

	case 3 :
		NVIC_IRQ9_EXTI3_DISABLE() ;
		break ;

	case 4 :
		NVIC_IRQ10_EXTI4_DISABLE() ;
		break ;

	case 5 :
	case 6 :
	case 7 :
	case 8 :
	case 9 :
		NVIC_IRQ23_EXTI5_9_DISABLE() ;
		break ;

	case 10 :
	case 11 :
	case 12 :
	case 13 :
	case 14 :
	case 15 :
		NVIC_IRQ40_EXTI10_15_DISABLE() ;
		break ;
	}
}

void EXTI_Update (EXTI_PinConfig_t* EXTI_Config) {
	// configure GPIO as alternative function input
	GPIO_PinConfig_t PinConfig ;
	PinConfig.GPIO_PinNumber = EXTI_Config->EXTI_Pin.GPIO_Pin ;
	PinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLOATING ;
	MCAL_GPIO_Init(EXTI_Config->EXTI_Pin.GPIO_Port, &PinConfig) ;

	// configure AFIO
	uint8_t AFIO_EXTICR_index = EXTI_Config->EXTI_Pin.EXTI_InputLineNumber / 4 ;
	uint8_t AFIO_EXTICR_position = ( EXTI_Config->EXTI_Pin.EXTI_InputLineNumber % 4 ) * 4 ;

	AFIO->EXTICR[AFIO_EXTICR_index] &= ~ (0xF << AFIO_EXTICR_position) ;
	AFIO->EXTICR[AFIO_EXTICR_index] |= (( AFIO_GPIO_EXTI_MAPPING(EXTI_Config->EXTI_Pin.GPIO_Port) & 0xF ) << AFIO_EXTICR_position ) ;

	// configure edge triggering
	EXTI->RTSR &= ~(1 << EXTI_Config->EXTI_Pin.EXTI_InputLineNumber) ;
	EXTI->FTSR &= ~(1 << EXTI_Config->EXTI_Pin.EXTI_InputLineNumber) ;

	if (EXTI_Config->Trigger == EXTI_Trigger_RISING) {
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_Pin.EXTI_InputLineNumber) ;
	}
	else if (EXTI_Config->Trigger == EXTI_Trigger_FALLING) {
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_Pin.EXTI_InputLineNumber) ;
	}
	else if (EXTI_Config->Trigger == EXTI_Trigger_ANYCHANGE) {
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_Pin.EXTI_InputLineNumber) ;
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_Pin.EXTI_InputLineNumber) ;
	}

	// update IRQ handling CallBack
	GP_IRQ_CallBack[EXTI_Config->EXTI_Pin.EXTI_InputLineNumber] = EXTI_Config->P_IRQ_CallBack ;

	// Enable / Disable Interrupt_MASK & NVIC
	if (EXTI_Config->IRQ_EN == EXTI_IRQ_ENABLE) {
		EXTI->IMR |= (1 << EXTI_Config->EXTI_Pin.EXTI_InputLineNumber) ;
		NVIC_Enable (EXTI_Config->EXTI_Pin.EXTI_InputLineNumber) ;
	}
	else {
		EXTI->IMR &= ~(1 << EXTI_Config->EXTI_Pin.EXTI_InputLineNumber) ;
		NVIC_Disable (EXTI_Config->EXTI_Pin.EXTI_InputLineNumber) ;
	}
}

/*
 * 		@Fn				-	MCAL_EXTI_Init
 * 		@brief			-	initialize EXTI required
 * 		@param[in]		-	Config (EXTI_GPIO_Mapping_t @ref EXTI_define , uint8_t Trigger @ref EXTI_Trigger_define , uint8_t IRQ_EN @ref EXTI_IRQ_EN_define)
 * 		@param[out]		-	none
 * 		@return value	-	none
 * 		Note			-	none
 */
void MCAL_EXTI_Init (EXTI_PinConfig_t* EXTI_Config) {
	EXTI_Update (EXTI_Config) ;

}

/*
 * 		@Fn				-	MCAL_EXTI_Update
 * 		@brief			-	initialize EXTI required
 * 		@param[in]		-	Config (EXTI_GPIO_Mapping_t @ref EXTI_define , uint8_t Trigger @ref EXTI_Trigger_define , uint8_t IRQ_EN @ref EXTI_IRQ_EN_define)
 * 		@param[out]		-	none
 * 		@return value	-	none
 * 		Note			-	none
 */
void MCAL_EXTI_Update (EXTI_PinConfig_t* EXTI_Config) {
	EXTI_Update (EXTI_Config) ;
}
/*
 * 		@Fn				-	MCAL_EXTI_DeInit
 * 		@brief			-	Reset the EXTI registers
 * 		@param[in]		-	none
 * 		@param[out]		-	none
 * 		@return value	-	none
 * 		Note			-	none
 */
void MCAL_EXTI_DeInit (void) {
	// Reset registers by putting the reset value
	EXTI->IMR   = 0x00000000 ;
	EXTI->EMR   = 0x00000000 ;
	EXTI->RTSR  = 0x00000000 ;
	EXTI->FTSR  = 0x00000000 ;
	EXTI->SWIER = 0x00000000 ;
	EXTI->PR 	= 0xFFFFFFFF ;

	// Disable IRQ from NVIC
	NVIC_IRQ6_EXTI0_DISABLE() ;
	NVIC_IRQ7_EXTI1_DISABLE() ;
	NVIC_IRQ8_EXTI2_DISABLE() ;
	NVIC_IRQ9_EXTI3_DISABLE() ;
	NVIC_IRQ10_EXTI4_DISABLE() ;
	NVIC_IRQ23_EXTI5_9_DISABLE() ;
	NVIC_IRQ40_EXTI10_15_DISABLE() ;
}

// ----------------------------------------- ISR Functions -----------------------------------------
void EXTI0_IRQHandler (void) {
	// clear corresponding bit in pending register
	EXTI->PR |= (1 << 0) ;

	// Call IRQ_CallBack
	GP_IRQ_CallBack[0]() ;

}
void EXTI1_IRQHandler (void) {
	// clear corresponding bit in pending register
	EXTI->PR |= (1 << 1) ;

	// Call IRQ_CallBack
	GP_IRQ_CallBack[1]() ;
}
void EXTI2_IRQHandler (void) {
	// clear corresponding bit in pending register
	EXTI->PR |= (1 << 2) ;

	// Call IRQ_CallBack
	GP_IRQ_CallBack[2]() ;
}
void EXTI3_IRQHandler (void) {
	// clear corresponding bit in pending register
	EXTI->PR |= (1 << 3) ;

	// Call IRQ_CallBack
	GP_IRQ_CallBack[3]() ;
}
void EXTI4_IRQHandler (void) {
	// clear corresponding bit in pending register
	EXTI->PR |= (1 << 4) ;

	// Call IRQ_CallBack
	GP_IRQ_CallBack[4]() ;
}
void EXTI9_5_IRQHandler (void) {
	if (EXTI->PR & (1 << 5)) {
		// clear corresponding bit in pending register
		EXTI->PR |= (1 << 5) ;

		// Call IRQ_CallBack
		GP_IRQ_CallBack[5]() ;
	}
	if (EXTI->PR & (1 << 6)) {
		// clear corresponding bit in pending register
		EXTI->PR |= (1 << 6) ;

		// Call IRQ_CallBack
		GP_IRQ_CallBack[6]() ;
	}
	if (EXTI->PR & (1 << 7)) {
		// clear corresponding bit in pending register
		EXTI->PR |= (1 << 7) ;

		// Call IRQ_CallBack
		GP_IRQ_CallBack[7]() ;
	}
	if (EXTI->PR & (1 << 8)) {
		// clear corresponding bit in pending register
		EXTI->PR |= (1 << 8) ;

		// Call IRQ_CallBack
		GP_IRQ_CallBack[8]() ;
	}
	if (EXTI->PR & (1 << 9)) {
		// clear corresponding bit in pending register
		EXTI->PR |= (1 << 9) ;

		// Call IRQ_CallBack
		GP_IRQ_CallBack[9]() ;
	}
}
void EXTI15_10_IRQHandler (void) {
	if (EXTI->PR & (1 << 10)) {
		// clear corresponding bit in pending register
		EXTI->PR |= (1 << 10) ;

		// Call IRQ_CallBack
		GP_IRQ_CallBack[10]() ;
	}
	if (EXTI->PR & (1 << 11)) {
		// clear corresponding bit in pending register
		EXTI->PR |= (1 << 11) ;

		// Call IRQ_CallBack
		GP_IRQ_CallBack[11]() ;
	}
	if (EXTI->PR & (1 << 12)) {
		// clear corresponding bit in pending register
		EXTI->PR |= (1 << 12) ;

		// Call IRQ_CallBack
		GP_IRQ_CallBack[12]() ;
	}
	if (EXTI->PR & (1 << 13)) {
		// clear corresponding bit in pending register
		EXTI->PR |= (1 << 13) ;

		// Call IRQ_CallBack
		GP_IRQ_CallBack[13]() ;
	}
	if (EXTI->PR & (1 << 14)) {
		// clear corresponding bit in pending register
		EXTI->PR |= (1 << 14) ;

		// Call IRQ_CallBack
		GP_IRQ_CallBack[14]() ;
	}
}
