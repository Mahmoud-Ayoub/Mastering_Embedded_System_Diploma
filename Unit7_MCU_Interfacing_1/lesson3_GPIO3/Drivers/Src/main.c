/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mahmoud Ayoub
 * @brief          : Control LEDs using push buttons on STM32F103C6
 ******************************************************************************
 */
#include "STM32F103C6.h"
#include "GPIO.h"

void clock_init (void) {
	CLK_EN_GPIOA() ;
	CLK_EN_GPIOB() ;
}
void Pins_init (void) {
	// configure PA1 as input floating
	GPIO_PinConfig_t PA1_config ;
	PA1_config.GPIO_PinNumber = GPIO_PIN_1 ;
	PA1_config.GPIO_MODE = GPIO_MODE_INPUT_FLOATING ;
	MCAL_GPIO_Init(GPIOA, &PA1_config) ;

	// configure PA13 as input floating
	GPIO_PinConfig_t PA13_config ;
	PA13_config.GPIO_PinNumber = GPIO_PIN_13 ;
	PA13_config.GPIO_MODE = GPIO_MODE_INPUT_FLOATING ;
	MCAL_GPIO_Init(GPIOA, &PA13_config) ;

	// configure PB1 as output push-pull
	GPIO_PinConfig_t PB1_config ;
	PB1_config.GPIO_PinNumber = GPIO_PIN_1 ;
	PB1_config.GPIO_MODE = GPIO_MODE_OUTPUT_PUSH_PULL ;
	PB1_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(GPIOB, &PB1_config) ;

	// configure PB13 as output push-pull
	GPIO_PinConfig_t PB13_config ;
	PB13_config.GPIO_PinNumber = GPIO_PIN_13 ;
	PB13_config.GPIO_MODE = GPIO_MODE_OUTPUT_PUSH_PULL ;
	PB13_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(GPIOB, &PB13_config) ;

}
int main(void)
{
	clock_init() ;
	Pins_init() ;
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1) ;        	// LED OFF
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 1) ;			// LED OFF
	int delay = 0 ;

	while (1) {
		if (MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0) {
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1) ;          // Toggle LED on PB1
			while (MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0) ;
		}

		if (MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13) == 1) {
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13) ;         // Toggle LED on PB13
			for (delay = 0 ; delay < 10000 ; delay ++) ;
		}
	}
}
