/*
 * GPIO.h
 *
 *      Author: Mahmoud Ayoub
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "STM32F103C6.h"

// =========================================================================
// 			Configuration MACROS
//==========================================================================
/*
 * 	@ref GPIO_PINS_define
 */
#define GPIO_PIN_0 			 			((uint16_t)0x0001)
#define GPIO_PIN_1 			 			((uint16_t)0x0002)
#define GPIO_PIN_2 			 			((uint16_t)0x0004)
#define GPIO_PIN_3 			 			((uint16_t)0x0008)
#define GPIO_PIN_4 			 			((uint16_t)0x0010)
#define GPIO_PIN_5 			 			((uint16_t)0x0020)
#define GPIO_PIN_6 				 		((uint16_t)0x0040)
#define GPIO_PIN_7 				 		((uint16_t)0x0080)
#define GPIO_PIN_8 				 		((uint16_t)0x0100)
#define GPIO_PIN_9 				 		((uint16_t)0x0200)
#define GPIO_PIN_10 			 			((uint16_t)0x0400)
#define GPIO_PIN_11 			 			((uint16_t)0x0800)
#define GPIO_PIN_12 			 			((uint16_t)0x1000)
#define GPIO_PIN_13 			 			((uint16_t)0x2000)
#define GPIO_PIN_14 			 			((uint16_t)0x4000)
#define GPIO_PIN_15 			 			((uint16_t)0x8000)
#define GPIO_PIN_ALL						((uint16_t)0xFFFF)

/*
 *	@ref GPIO_MODE_define
 */
#define GPIO_MODE_ANALOG 						(0x00u)
#define GPIO_MODE_INPUT_FLOATING 					(0x01u)
#define GPIO_MODE_INPUT_PULL_UP 					(0x02u)
#define GPIO_MODE_INPUT_PULL_DOWN 					(0x03u)
#define GPIO_MODE_OUTPUT_PUSH_PULL 					(0x04u)
#define GPIO_MODE_OUTPUT_OPEN_DRAIN 					(0x05u)
#define GPIO_MODE_AF_PUSH_PULL 						(0x06u)
#define GPIO_MODE_AF_OPEN_DRAIN 					(0x07u)
#define GPIO_MODE_AF_INPUT 						(0x08u)

/*
 * 	@ref GPIO_SPEED_define
 */
#define GPIO_SPEED_10M							(0x01u)
#define GPIO_SPEED_2M							(0x02u)
#define GPIO_SPEED_50M							(0x03u)

/*
 * @ref GPIO_PIN_state
 */
#define GPIO_PIN_SET	1
#define GPIO_PIN_RESET 	0

/*
 * @ref GPIO_RETURN_LOCK
 */
#define GPIO_LOCK_SUCCEED 	1
#define GPIO_LOCK_ERROR		0
// =========================================================================
// 			Configuration Structures
//==========================================================================
typedef struct {
	uint16_t GPIO_PinNumber ;       				// specifies the GPIO pins to be configured
									// This parameter can be a value of @ref GPIO_PINS_define

	uint8_t GPIO_MODE ;						// specifies the operating mode for the selected pins
									// This parameter can be a value of @ref GPIO_MODE_define

	uint8_t GPIO_Output_Speed ; 					// specifies the output speed for selected pins
									// This parameter can be a value of @ref GPIO_SPEED_define

}GPIO_PinConfig_t;

// =========================================================================
// 				APIs
//==========================================================================
void MCAL_GPIO_Init (GPIO_TypeDef* GPIOx , GPIO_PinConfig_t* PinConfig) ;
void MCAL_GPIO_DeInit (GPIO_TypeDef* GPIOx) ;
uint8_t MCAL_GPIO_ReadPin (GPIO_TypeDef* GPIOx , uint16_t PinNumber) ;
uint16_t MCAL_GPIO_ReadPort (GPIO_TypeDef* GPIOx) ;
void MCAL_GPIO_WritePin (GPIO_TypeDef* GPIOx , uint16_t PinNumber , uint8_t Value) ;
void MCAL_GPIO_WritePort (GPIO_TypeDef* GPIOx , uint16_t Value) ;
void MCAL_GPIO_TogglePin (GPIO_TypeDef* GPIOx , uint16_t PinNumber) ;
uint8_t MCAL_GPIO_LockPin (GPIO_TypeDef* GPIOx , uint16_t PinNumber) ;
#endif /* INC_GPIO_H_ */
