/*
 * I2C_Slave_EEPROM.c
 *
 *      Author: Mahmoud Ayoub
 */
#include "I2C_Slave_EEPROM.h"

void HAL_EEPROM_Init (void) {
	I2C_Config_t eeprom_cfg ;
	eeprom_cfg.Ack_control = I2C_Ack_ENABLE ;
	eeprom_cfg.clock_speed = I2C_CLK_SM_100k ;
	eeprom_cfg.I2C_mode = I2C_MODE_I2C ;
	eeprom_cfg.p_slave_callback = NULL ;
	eeprom_cfg.clock_stretch_mode = I2C_CLK_STRETCH_ENABLE ;
	MCAL_I2C_GPIO_Pins(I2C1) ;
	MCAL_I2C_Init(I2C1, &eeprom_cfg) ;
}

uint8_t HAL_EEPROM_Write (uint32_t Memory_Address, uint8_t *data_buffer, uint32_t datalen) {
	int i = 0;
	uint8_t Buffer[256];
	Buffer[0] = (uint8_t)(Memory_Address >> 8);		//upper eeprom address
	Buffer[1] = (uint8_t)(Memory_Address);			//lower eeprom address
	for (i=2 ; i<(datalen+2) ; i++) {
		Buffer[i] = data_buffer[i-2] ;
	}

	MCAL_I2C_Master_Tx(I2C1, EEPROM_SLAVE_ADDRESS, Buffer, datalen+2, with_stop, non_repeated_start) ;
	return 0 ;
}

uint8_t HAL_EEPROM_Read (uint32_t Memory_Address, uint8_t *data_buffer, uint32_t datalen) {
	uint8_t Buffer[2];
	Buffer[0] = (uint8_t)(Memory_Address >> 8);		//upper eeprom address
	Buffer[1] = (uint8_t)(Memory_Address);			//lower eeprom address
	MCAL_I2C_Master_Tx(I2C1, EEPROM_SLAVE_ADDRESS, Buffer, 2, without_stop, non_repeated_start);
	MCAL_I2C_Master_Rx(I2C1, EEPROM_SLAVE_ADDRESS, data_buffer, datalen, with_stop, repeated_start);
	return 0;
}

