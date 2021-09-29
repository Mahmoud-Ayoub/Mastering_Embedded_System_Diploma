/*
 * Keypad.c
 *
 *  Author: Mahmoud Ayoub
 */ 


#include "Keypad.h"
/*
Description : function to initialize the port which keypad is connected (low nibble rows as OUTPUTs) , (high nibble cols as INPUTS)
inputs		:	 none
outputs		:    none  
 */
void KEYPAD_init (void) {
	// initialization for ports (LSB is output row) and (MSB is input columns)
	GPIO_PinConfig_t R0_config ;
	R0_config.GPIO_PinNumber = R0 ;
	R0_config.GPIO_MODE = GPIO_MODE_OUTPUT_PUSH_PULL ;
	R0_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT, &R0_config) ;

	GPIO_PinConfig_t R1_config ;
	R1_config.GPIO_PinNumber = R1 ;
	R1_config.GPIO_MODE = GPIO_MODE_OUTPUT_PUSH_PULL ;
	R1_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT, &R1_config) ;

	GPIO_PinConfig_t R2_config ;
	R2_config.GPIO_PinNumber = R2 ;
	R2_config.GPIO_MODE = GPIO_MODE_OUTPUT_PUSH_PULL ;
	R2_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT, &R2_config) ;

	GPIO_PinConfig_t R3_config ;
	R3_config.GPIO_PinNumber = R3 ;
	R3_config.GPIO_MODE = GPIO_MODE_OUTPUT_PUSH_PULL ;
	R3_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT, &R3_config) ;

	GPIO_PinConfig_t COL0_config ;
	COL0_config.GPIO_PinNumber = COL0 ;
	COL0_config.GPIO_MODE = GPIO_MODE_INPUT_PULL_DOWN ;
	MCAL_GPIO_Init(KEYPAD_PORT, &COL0_config) ;

	GPIO_PinConfig_t COL1_config ;
	COL1_config.GPIO_PinNumber = COL1 ;
	COL1_config.GPIO_MODE = GPIO_MODE_INPUT_PULL_DOWN ;
	MCAL_GPIO_Init(KEYPAD_PORT, &COL1_config) ;


	GPIO_PinConfig_t COL2_config ;
	COL2_config.GPIO_PinNumber = COL2 ;
	COL2_config.GPIO_MODE = GPIO_MODE_INPUT_PULL_DOWN ;
	MCAL_GPIO_Init(KEYPAD_PORT, &COL2_config) ;

	GPIO_PinConfig_t COL3_config ;
	COL3_config.GPIO_PinNumber = COL3 ;
	COL3_config.GPIO_MODE = GPIO_MODE_INPUT_PULL_DOWN ;
	MCAL_GPIO_Init(KEYPAD_PORT, &COL3_config) ;
}

/*
Description : function to read value from keypad 
inputs		:	 none
outputs		:    value of pressed button on keypad 
 */
char KEYPAD_read (void) {
	KEYPAD_init()  ;
	char row_data ;
	while (1){
		for (row_data=1 ; row_data<=8 ; row_data = row_data << 1 ){         // loop for sending ones for rows
			OUTPUT_ROW = row_data ;
			wait_ms(1) ;
			if (row_data == 1 ){
				switch(INPUT_COL){
				case 1  : return 'P' ; break;
				case 2  : return '0' ; break;
				case 4  : return '=' ; break;
				case 8  : return '+' ; break;
				}

			}
			else if (row_data == 2 ){
				switch(INPUT_COL){
				case 1  : return '1' ; break;
				case 2  : return '2' ; break;
				case 4  : return '3' ; break;
				case 8  : return '-' ; break;
				}

			}
			else if (row_data == 4 ){
				switch(INPUT_COL){
				case 1  : return '4' ; break;
				case 2  : return '5' ; break;
				case 4  : return '6' ; break;
				case 8  : return '*' ; break;
				}

			}
			else if (row_data == 8 ){
				switch(INPUT_COL){
				case 1  : return '7' ; break;
				case 2  : return '8' ; break;
				case 4  : return '9' ; break;
				case 8  : return '/' ; break;
				}
			}
		}
	}
}

/*
Description : function to handle pressing on keypad buttons
inputs		:	 none
outputs		:    none
 */
void KEYPAD_wait (void) {
	while(INPUT_COL) ;
}
