/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mahmoud Ayoub
 * @brief          : STM32F103C6
 ******************************************************************************
 */
#include "STM32F103C6.h"
#include "RCC.h"
#include "I2C_Slave_EEPROM.h"


void clock_init (void) {
	CLK_EN_GPIOA() ;
	CLK_EN_GPIOB() ;
	CLK_EN_AFIO() ;
}
int main(void)
{
	clock_init() ;
	HAL_EEPROM_Init();

	//Test Case 1
	uint8_t ch1[] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07};
	uint8_t ch2[7] = {0};
	HAL_EEPROM_Write(0xAF, ch1, 7);
	HAL_EEPROM_Read(0xAF, ch2, 7);

	//Test Case 2
	ch1[0] = 0xA;
	ch1[1] = 0xB;
	ch1[2] = 0xC;
	ch1[3] = 0xD;
	HAL_EEPROM_Write(0xFFF, ch1, 4);
	HAL_EEPROM_Read(0xFFF, ch2, 4);

	while (1) {

	}
	return 0 ;

}
