/*
 * I2C_Slave_EEPROM.h
 *
 *      Author: Mahmoud Ayoub
 */

#ifndef INCLUDES_I2C_SLAVE_EEPROM_H_
#define INCLUDES_I2C_SLAVE_EEPROM_H_

#include "I2C.h"

#define EEPROM_SLAVE_ADDRESS	0x2A

void HAL_EEPROM_Init (void) ;
uint8_t HAL_EEPROM_Write (uint32_t Memory_Address, uint8_t *data_buffer, uint32_t datalen) ;
uint8_t HAL_EEPROM_Read (uint32_t Memory_Address, uint8_t *data_buffer, uint32_t datalen) ;



#endif /* INCLUDES_I2C_SLAVE_EEPROM_H_ */
