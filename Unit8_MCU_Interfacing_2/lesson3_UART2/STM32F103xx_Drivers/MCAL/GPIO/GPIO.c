/*
 * GPIO.c
 *
 *      Author: Mahmoud Ayoub
 */
#include "GPIO.h"

static GPIO_CRLH_GetPosition (uint16_t PinNumber) {
	switch (PinNumber) {
	case GPIO_PIN_0 :
		return 0 ;
		break ;
	case GPIO_PIN_1 :
		return 4 ;
		break ;
	case GPIO_PIN_2 :
		return 8 ;
		break ;
	case GPIO_PIN_3 :
		return 12 ;
		break ;
	case GPIO_PIN_4 :
		return 16 ;
		break ;
	case GPIO_PIN_5 :
		return 20 ;
		break ;
	case GPIO_PIN_6 :
		return 24 ;
		break ;
	case GPIO_PIN_7 :
		return 28 ;
		break ;
	case GPIO_PIN_8 :
		return 0 ;
		break ;
	case GPIO_PIN_9 :
		return 4 ;
		break ;
	case GPIO_PIN_10 :
		return 8 ;
		break ;
	case GPIO_PIN_11 :
		return 12 ;
		break ;
	case GPIO_PIN_12 :
		return 16 ;
		break ;
	case GPIO_PIN_13 :
		return 20 ;
		break ;
	case GPIO_PIN_14 :
		return 24 ;
		break ;
	case GPIO_PIN_15 :
		return 28 ;
		break ;
	}
}
/*
 * 		@Fn			-	MCAL_GPIO_Init
 * 		@brief			-	Initializes the GPIOx pin according to the specified parameters in PinConfig
 * 		@param[in]		-	GPIOx : where x can be (A..G) to select GPIO peripheral
 * 		@param[in]		-	PinConfig is a pointer to GPIO_PinConfig_t structure which contains GPIO pin configuration
 * 		@param[out]		-	none
 * 		@return value		-	none
 * 		Note			-	STM32F103C6 has GPIO A,B,C,D,E,F,G Modules
 * 						But LQFP48 Package has only GPIO A , B , part of C , part of D
 *
 */
void MCAL_GPIO_Init (GPIO_TypeDef* GPIOx , GPIO_PinConfig_t* PinConfig) {

	uint8_t Pin_Config_Value = 0 ;

	// Port Configuration register Low (GPIOx_CRL) configure PINS from 0 to 7
	// Port Configuration register High (GPIOx_CRH) configure PINS from 8 to 15
	volatile uint32_t* ConfigReg = NULL ;
	ConfigReg = (PinConfig->GPIO_PinNumber < GPIO_PIN_8 ) ? (&GPIOx->CRL) : (&GPIOx->CRH) ;

	// clear CNF and MODE
	(*ConfigReg) &= ~ (0xF << GPIO_CRLH_GetPosition(PinConfig->GPIO_PinNumber)) ;

	// if pin is output
	if ( (PinConfig->GPIO_MODE == GPIO_MODE_AF_OPEN_DRAIN) || (PinConfig->GPIO_MODE == GPIO_MODE_AF_PUSH_PULL) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PUSH_PULL) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_OPEN_DRAIN) ) {
		// Set CNF and MODE
		Pin_Config_Value = ( (((PinConfig->GPIO_MODE - 4) << 2) | (PinConfig->GPIO_Output_Speed)) & 0x0F ) ;
		(*ConfigReg) |= ( (Pin_Config_Value) << (GPIO_CRLH_GetPosition(PinConfig->GPIO_PinNumber)) ) ;
	}
	// if pin is input
	else {
		if ((PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLOATING) || (PinConfig->GPIO_MODE == GPIO_MODE_ANALOG)) {
			// Set CNF and MODE
			Pin_Config_Value = ( (((PinConfig->GPIO_MODE) << 2) | (0x0)) & 0x0F ) ;
			(*ConfigReg) |= ( (Pin_Config_Value) << (GPIO_CRLH_GetPosition(PinConfig->GPIO_PinNumber)) ) ;
		}
		else if (PinConfig->GPIO_MODE == GPIO_MODE_AF_INPUT) {
			// Set CNF and MODE
			Pin_Config_Value = ( (((PinConfig->GPIO_MODE) << 2) | (0x0)) & 0x0F ) ;
			(*ConfigReg) |= ( (Pin_Config_Value) << (GPIO_CRLH_GetPosition(PinConfig->GPIO_PinNumber)) ) ;
		}
		else {
			// input PULL UP / PULL DOWN
			// Set CNF and MODE
			Pin_Config_Value = ( (((GPIO_MODE_INPUT_PULL_UP) << 2) | (0x0)) & 0x0F ) ;
			if (PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PULL_UP) {
				GPIOx->ODR |= PinConfig->GPIO_PinNumber ;
			}
			else {
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber) ;
			}
			(*ConfigReg) |= ( (Pin_Config_Value) << (GPIO_CRLH_GetPosition(PinConfig->GPIO_PinNumber)) ) ;

		}
	}

}

/*
 * 		@Fn			-	MCAL_GPIO_DeInit
 * 		@brief			-	Reset the GPIOx registers
 * 		@param[in]		-	GPIOx : where x can be (A..G) to select GPIO peripheral
 * 		@param[out]		-	none
 * 		@return value		-	none
 * 		Note			-	none
 */
void MCAL_GPIO_DeInit (GPIO_TypeDef* GPIOx) {
	if (GPIOx == GPIOA) {
		RCC->APB2RSTR |= (1 << 2) ;
		RCC->APB2RSTR &= ~(1 << 2) ;
	}
	else if (GPIOx == GPIOB) {
		RCC->APB2RSTR |= (1 << 3) ;
		RCC->APB2RSTR &= ~(1 << 3) ;
	}
	else if (GPIOx == GPIOC) {
		RCC->APB2RSTR |= (1 << 4) ;
		RCC->APB2RSTR &= ~(1 << 4) ;
	}
	else if (GPIOx == GPIOD) {
		RCC->APB2RSTR |= (1 << 5) ;
		RCC->APB2RSTR &= ~(1 << 5) ;
	}
	else if (GPIOx == GPIOE) {
		RCC->APB2RSTR |= (1 << 6) ;
		RCC->APB2RSTR &= ~(1 << 6) ;
	}
	else if (GPIOx == GPIOF) {
		RCC->APB2RSTR |= (1 << 7) ;
		RCC->APB2RSTR &= ~(1 << 7) ;
	}
	else if (GPIOx == GPIOG) {
		RCC->APB2RSTR |= (1 << 8) ;
		RCC->APB2RSTR &= ~(1 << 8) ;
	}
}

/*
 * 		@Fn			-	MCAL_GPIO_ReadPin
 * 		@brief			-	Read data on specified Pin on the GPIOx
 * 		@param[in]		-	GPIOx : where x can be (A..G) to select GPIO peripheral
 * 		@param[in]		-	PinNumber : where PinNumber can be (GPIO_PIN_0 .. 15) according to @ref GPIO_PINS_define
 * 		@param[out]		- 	none
 * 		@return value		-	value of input pin according to @ref GPIO_PIN_state
 * 		Note			-	none
 */
uint8_t MCAL_GPIO_ReadPin (GPIO_TypeDef* GPIOx , uint16_t PinNumber) {
	if ( (GPIOx->IDR & PinNumber) != (uint32_t)GPIO_PIN_RESET) {
		return GPIO_PIN_SET ;
	}
	else {
		return GPIO_PIN_RESET ;
	}
}

/*
 * 		@Fn			-	MCAL_GPIO_ReadPort
 * 		@brief			-	Read data on specified Port
 * 		@param[in]		-	GPIOx : where x can be (A..G) to select GPIO peripheral
 * 		@param[out]		-	none
 * 		@return value		-	value of input port
 * 		Note			-	none
 */
uint16_t MCAL_GPIO_ReadPort (GPIO_TypeDef* GPIOx) {
	return (uint16_t)GPIOx->IDR ;
}

/*
 * 		@Fn			-	MCAL_GPIO_WritePin
 * 		@brief			-	Write data on specified Pin on the GPIOx
 * 		@param[in]		-	GPIOx : where x can be (A..G) to select GPIO peripheral
 * 		@param[in]		-	PinNumber : where PinNumber can be (GPIO_PIN_0 .. 15) according to @ref GPIO_PINS_define
 * 		@param[in]		-	Value required to be written on the specified pin
 * 		@param[out]		- 	none
 * 		@return value		-	none
 * 		Note			-	none
 */
void MCAL_GPIO_WritePin (GPIO_TypeDef* GPIOx , uint16_t PinNumber , uint8_t Value) {
	if (Value != GPIO_PIN_RESET) {
		GPIOx->ODR |= ((uint32_t)PinNumber) ;
	}
	else {
		GPIOx->ODR &= ~((uint32_t)PinNumber) ;
	}
}

/*
 * 		@Fn			-	MCAL_GPIO_WritePort
 * 		@brief			-	Write data on specified Port
 * 		@param[in]		-	GPIOx : where x can be (A..G) to select GPIO peripheral
 * 		@param[in]		-	Value required to be written on the specified port
 * 		@param[out]		- 	none
 * 		@return value		-	none
 * 		Note			-	none
 */
void MCAL_GPIO_WritePort (GPIO_TypeDef* GPIOx , uint16_t Value) {
	GPIOx->ODR = (uint32_t)Value ;
}

/*
 * 		@Fn			-	MCAL_GPIO_TogglePin
 * 		@brief			-	Toggle Pin on the GPIOx
 * 		@param[in]		-	GPIOx : where x can be (A..G) to select GPIO peripheral
 * 		@param[in]		-	PinNumber : where PinNumber can be (GPIO_PIN_0 .. 15) according to @ref GPIO_PINS_define
 * 		@param[out]		- 	none
 * 		@return value		-	none
 * 		Note			-	none
 */
void MCAL_GPIO_TogglePin (GPIO_TypeDef* GPIOx , uint16_t PinNumber) {
	GPIOx->ODR ^= (PinNumber) ;
}

/*
 * 		@Fn			-	MCAL_GPIO_LockPin
 * 		@brief			-	Lock Pin on the GPIOx
 * 		@param[in]		-	GPIOx : where x can be (A..G) to select GPIO peripheral
 * 		@param[in]		-	PinNumber : where PinNumber can be (GPIO_PIN_0 .. 15) according to @ref GPIO_PINS_define
 * 		@param[out]		- 	none
 * 		@return value		-	OK if lock succeed or ERROR is lock failed according to @ref GPIO_RETURN_LOCK
 * 		Note			-	none
 */
uint8_t MCAL_GPIO_LockPin (GPIO_TypeDef* GPIOx , uint16_t PinNumber) {
	volatile uint32_t temp = 1 << 16 ;
	temp |= PinNumber ;
	GPIOx->LCKR = temp ;
	GPIOx->LCKR = PinNumber ;
	GPIOx->LCKR = temp ;
	temp = GPIOx->LCKR ;
	if ( (uint32_t)(GPIOx->LCKR & (1<<16)) ) {
		return GPIO_LOCK_SUCCEED ;
	}
	else {
		return GPIO_LOCK_ERROR ;
	}
}
