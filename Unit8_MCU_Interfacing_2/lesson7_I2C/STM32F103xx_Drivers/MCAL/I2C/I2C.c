/*
 * I2C.c
 *
 *      Author: Mahmoud Ayoub
 */

#include "I2C.h"
// --------------------------------- Global Variables ------------------------------------------------
I2C_Config_t g_I2C_Cfg[2] = {NULL , NULL} ;
//===================================================================================================

// ---------------------------------Generic MACROS ------------------------------------------------
#define I2C1_index	0
#define I2C2_index	1
//===================================================================================================


// --------------------------------- APIs ------------------------------------------------------------
/*
 * 		@Fn				-	MCAL_I2C_Init
 * 		@brief			-	Initialize I2C module
 * 		@param[in]		-	I2Cx (I2C1 , I2C2)
 * 						 	I2Cx configurations required
 * 		@param[out]		-	none
 * 		@return value	-	none
 * 		Note			-	Configuration MACROS can be found in I2C.h
 */
void MCAL_I2C_Init (I2C_TypeDef* I2Cx , I2C_Config_t* I2C_Cfg) {
	/*
	 * The following is the required sequence in master mode.
		• Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
		• Configure the clock control registers
		• Configure the rise time register
		• Program the I2C_CR1 register to enable the peripheral
		• Set the START bit in the I2C_CR1 register to generate a Start condition

		The peripheral input clock frequency must be at least:
		• 2 MHz in Sm mode
		• 4 MHz in Fm mode
	 *
	 */

	uint16_t tempreg = 0 ;
	uint16_t freq_value = 0 ;
	uint16_t CCR_result = 0 ;
	uint32_t pclk1 = 8000000 ;

	// Enable RCC
	if (I2Cx == I2C1) {
		CLK_EN_I2C1() ;
		g_I2C_Cfg[I2C1_index] = *I2C_Cfg ;
	}
	else {
		CLK_EN_I2C2() ;
		g_I2C_Cfg[I2C2_index] = *I2C_Cfg ;
	}

	if (I2C_Cfg->I2C_mode == I2C_MODE_I2C) {

		// • Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
		// init timing
		tempreg = I2Cx->CR2 ;

		// clear freq bits in CR2 register
		I2Cx->CR2 &= ~(I2C_CR2_FREQ_Msk) ;

		// get pclk1
		pclk1 = MCAL_RCC_Get_PClk1_Freq() ;

		// assign freq value in CR2 register
		freq_value = (uint16_t)(pclk1 / 1000000) ;

		tempreg |= freq_value ;
		I2Cx->CR2 = tempreg ;

		// • Configure the clock control registers in I2C_CCR  " CCR = (pclk1) / (2 * i2c_clk) "

		// make sure that i2c peripheral is disabled
		I2Cx->CR1 &= ~(I2C_CR1_PE) ;

		tempreg = 0 ;

		// check for clock speed mode
		if ( (I2C_Cfg->clock_speed == I2C_CLK_SM_50k) || (I2C_Cfg->clock_speed == I2C_CLK_SM_100k) ) {
			CCR_result = (uint16_t)(pclk1 / (I2C_Cfg->clock_speed << 1) ) ;
			tempreg |= CCR_result ;
			I2Cx->CCR = tempreg ;

			// • Configure the rise time register
			I2Cx->TRISE = freq_value + 1 ;
		}

		// • Program the I2C_CR1 register to enable the peripheral
		tempreg = I2Cx->CR1 ;
		tempreg |= (uint16_t)(I2C_Cfg->Ack_control | I2C_Cfg->I2C_mode | I2C_Cfg->clock_stretch_mode) ;
		I2Cx->CR1 = tempreg ;

		// OAR1 & OAR2 configuration
		tempreg = 0 ;
		if (I2C_Cfg->slave_device_address.Enable_Dual_Address == 1) {
			tempreg = I2C_OAR2_ENDUAL ;
			tempreg |= I2C_Cfg->slave_device_address.secondary_address << I2C_OAR2_ADD2_Pos ;
			I2Cx->OAR2 = tempreg ;
		}
		tempreg = 0 ;
		tempreg |= I2C_Cfg->slave_device_address.primary_address << 1 ;
		tempreg |= I2C_Cfg->slave_device_address.addressing_slave_mode ;
		I2Cx->OAR1 = tempreg ;

		// if operates in slave mode (enable interrupt)
		if (I2C_Cfg->p_slave_callback != NULL) {
			I2Cx->CR2 |= I2C_CR2_ITBUFEN ;
			I2Cx->CR2 |= I2C_CR2_ITEVTEN ;
			I2Cx->CR2 |= I2C_CR2_ITERREN ;
			if (I2Cx == I2C1) {
				NVIC_IRQ31_I2C1_EV_ENABLE() ;
				NVIC_IRQ32_I2C1_ER_ENABLE() ;
			}
			else if (I2Cx == I2C2) {
				NVIC_IRQ33_I2C2_EV_ENABLE() ;
				NVIC_IRQ34_I2C2_ER_ENABLE() ;
			}
		}

		I2Cx->CR1 |= I2C_CR1_PE ;

	}
}

/*
 * 		@Fn				-	MCAL_I2C_DeInit
 * 		@brief			-	Reset I2C module
 * 		@param[in]		-	I2Cx (I2C1 , I2C2)
 * 		@param[out]		-	none
 * 		@return value	-	none
 * 		Note			-	none
 */
void MCAL_I2C_DeInit (I2C_TypeDef* I2Cx) {
	if (I2Cx == I2C1) {
		NVIC_IRQ31_I2C1_EV_DISABLE() ;
		NVIC_IRQ32_I2C1_ER_DISABLE() ;
		I2C1_RESET() ;
	}
	else if (I2Cx == I2C2) {
		NVIC_IRQ33_I2C2_EV_DISABLE() ;
		NVIC_IRQ34_I2C2_ER_DISABLE() ;
		I2C2_RESET() ;
	}
}

/*
 * 		@Fn				-	MCAL_SPI_GPIO_Pins
 * 		@brief			-	Initialize GPIO AF pins for (SCL , SDA)
 * 		@param[in]		-	I2Cx (I2C1 , I2C2)
 * 		@param[out]		-	none
 * 		@return value	-	none
 * 		Note			-	required AF modes can be found in TRM @ section 9.1.11 GPIO configurations for device peripherals
 *							AFIO pins can be found in TRM @ section 9.3 Alternate function I/O
 */
void MCAL_I2C_GPIO_Pins (I2C_TypeDef* I2Cx) {
	/*
	 * I2Cx_SCL 	I2C clock 		Alternate function open drain
	 * I2Cx_SDA 	I2C Data 		I/O Alternate function open drain
	 */
	GPIO_PinConfig_t pin_config ;
	if (I2Cx == I2C1) {
		/*
		 * I2C1_SCL		PB6				Alternate function open drain
		 * I2C1_SDA		PB7				Alternate function open drain
		 */
		pin_config.GPIO_MODE = GPIO_MODE_AF_OPEN_DRAIN ;
		pin_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
		pin_config.GPIO_PinNumber = GPIO_PIN_6 ;
		MCAL_GPIO_Init(GPIOB, &pin_config) ;

		pin_config.GPIO_MODE = GPIO_MODE_AF_OPEN_DRAIN ;
		pin_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
		pin_config.GPIO_PinNumber = GPIO_PIN_7 ;
		MCAL_GPIO_Init(GPIOB, &pin_config) ;

	}
	else if (I2Cx == I2C2) {

		/*
		 * I2C2_SCL		PB10			Alternate function open drain
		 * I2C2_SDA		PB11			Alternate function open drain
		 */
		pin_config.GPIO_MODE = GPIO_MODE_AF_OPEN_DRAIN ;
		pin_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
		pin_config.GPIO_PinNumber = GPIO_PIN_10 ;
		MCAL_GPIO_Init(GPIOB, &pin_config) ;

		pin_config.GPIO_MODE = GPIO_MODE_AF_OPEN_DRAIN ;
		pin_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
		pin_config.GPIO_PinNumber = GPIO_PIN_11 ;
		MCAL_GPIO_Init(GPIOB, &pin_config) ;
	}
}

/*
 * 		@Fn				-	MCAL_I2C_Master_Tx
 * 		@brief			-	Send Data over I2C by Master
 * 		@param[in]		-	I2Cx (I2C1 , I2C2),
 * 							Slave Address,
 * 							pointer to data buffer ,
 * 							data length ,
 * 						 	with stop or without stop,
 * 						 	start or repeated start
 * 		@param[out]		-	none
 * 		@return value	-	none
 * 		Note			-	none
 */
void MCAL_I2C_Master_Tx (I2C_TypeDef* I2Cx , uint16_t slave_address , uint8_t* data_buffer , uint32_t datalen , EN_Stop_Condition stop_cond , EN_Start start) {
	int i = 0 ;

	// generate start bit
	I2C_Generate_Start (I2Cx, enable, non_repeated_start) ;

	// wait for EV5 : SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while (!(I2C_Get_Flag_Status(I2Cx, EV5))) ;

	// write slave address on data register
	I2C_Send_Address(I2Cx, slave_address, Transmit) ;

	// wait for EV6 : ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while (!(I2C_Get_Flag_Status(I2Cx, EV6))) ;

	// check for Busy, MSL , TXE , TRA
	while (!(I2C_Get_Flag_Status(I2Cx, Master_Transmitter_Event))) ;

	for (i=0 ; i<datalen ; i++) {
		I2Cx->DR = data_buffer[i] ;
		// wait for EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
		while (!(I2C_Get_Flag_Status(I2Cx, EV8))) ;
	}

	// check stop condition
	if (stop_cond == with_stop) {
		I2C_Generate_Stop (I2Cx , enable) ;
	}
}

/*
 * 		@Fn				-	MCAL_I2C_Master_Rx
 * 		@brief			-	Receive Data over I2C by Master
 * 		@param[in]		-	I2Cx (I2C1 , I2C2),
 * 							Slave Address,
 * 							pointer to data buffer ,
 * 							data length ,
 * 						 	with stop or without stop,
 * 						 	start or repeated start
 * 		@param[out]		-	none
 * 		@return value	-	none
 * 		Note			-	none
 */
void MCAL_I2C_Master_Rx (I2C_TypeDef* I2Cx , uint16_t slave_address , uint8_t* data_buffer , uint32_t datalen , EN_Stop_Condition stop_cond , EN_Start start) {
	int i = 0 ;

	uint8_t index = I2Cx == I2C1 ? I2C1_index : I2C2_index;

	// generate start bit
	I2C_Generate_Start (I2Cx, enable, non_repeated_start) ;

	// wait for EV5 : SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while (!(I2C_Get_Flag_Status(I2Cx, EV5))) ;

	// write slave address on data register
	I2C_Send_Address(I2Cx, slave_address, Receive) ;

	// wait for EV6 : ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while (!(I2C_Get_Flag_Status(I2Cx, EV6))) ;

	I2C_ACKConfig(I2Cx , enable) ;

	if (datalen) {
		for (i=datalen ; i>1 ; i--) {
			// wait for EV7 : RXNE = 1 cleared by reading DR register
			while (!(I2C_Get_Flag_Status(I2Cx, EV7))) ;

			// read data from DR register
			*data_buffer = I2Cx->DR ;
			data_buffer++ ;
		}
		// Send NACK
		I2C_ACKConfig(I2Cx , disable) ;
	}

	// check stop condition
	if (stop_cond == with_stop) {
		I2C_Generate_Stop (I2Cx , enable) ;
	}
	// Re-enable automatic ACK
	if(g_I2C_Cfg[index].Ack_control == I2C_Ack_ENABLE)
		I2C_ACKConfig(I2Cx, enable);
	else
		I2C_ACKConfig(I2Cx, disable);
}

/*
 * 		@Fn				-	MCAL_I2C_Slave_Tx
 * 		@brief			-	Send Data over I2C by Slave
 * 		@param[in]		-	I2Cx (I2C1 , I2C2),
 * 							data buffer
 * 		@param[out]		-	none
 * 		@return value	-	none
 * 		Note			-	none
 */
void MCAL_I2C_Slave_Tx (I2C_TypeDef* I2Cx , uint8_t data) {
	I2Cx->DR = data ;
}

/*
 * 		@Fn				-	MCAL_I2C_Slave_Rx
 * 		@brief			-	Receive Data over I2C by Slave
 * 		@param[in]		-	I2Cx (I2C1 , I2C2),
 * 		@param[out]		-	data buffer
 * 		@return value	-	none
 * 		Note			-	none
 */
uint8_t MCAL_I2C_Slave_Rx (I2C_TypeDef* I2Cx) {
	return (uint8_t)I2Cx->DR ;
}

//===================================================================================================

// --------------------------------- Specific APIs ------------------------------------------------------------

void I2C_Generate_Start  (I2C_TypeDef* I2Cx , EN_Functional_state NewState , EN_Start start) {
	if (start == non_repeated_start){
		// check for the bus is idle or NOT
		/*
		 * Bit 1 BUSY: Bus busy in SR2
			0: No communication on the bus
			1: Communication ongoing on the bus
		 */
		while (I2C_Get_Flag_Status(I2Cx, I2C_Flag_Busy)) ;   // wait for bus to be idle
	}
	/*
	 * Bit 8 START: Start generation in CR1
			This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
			In Master Mode:
				0: No Start generation
				1: Repeated start generation
			In Slave mode:
				0: No Start generation
				1: Start generation when the bus is free
	 */
	if (NewState != disable) {
		I2Cx->CR1 |= I2C_CR1_START ;
	}
	else {
		I2Cx->CR1 &= ~(I2C_CR1_START) ;
	}

}

EN_Flag_Status I2C_Get_Flag_Status (I2C_TypeDef* I2Cx , EN_Status flag) {
	EN_Flag_Status bitstatus = Reset ;
	uint32_t flag1 = 0 , flag2 = 0 ;
	uint32_t last_event = 0 ;
	switch (flag) {
	case I2C_Flag_Busy :
		if (I2Cx->SR2 & I2C_SR2_BUSY)
			bitstatus = Set ;
		else
			bitstatus = Reset ;
		break ;

	case EV5 :
		if (I2Cx->SR1 & I2C_SR1_SB)
			bitstatus = Set ;
		else
			bitstatus = Reset ;
		break ;

	case EV6 :
		if (I2Cx->SR1 & I2C_SR1_ADDR)
			bitstatus = Set ;
		else
			bitstatus = Reset ;
		break ;

	case EV8 :
		if (I2Cx->SR1 & I2C_SR1_TXE)
			bitstatus = Set ;
		else
			bitstatus = Reset ;
		break ;

	case EV7 :
		if (I2Cx->SR1 & I2C_SR1_RXNE)
			bitstatus = Set ;
		else
			bitstatus = Reset ;
		break ;

	case Master_Transmitter_Event :
	{
		flag1 = Master_Transmitter_Event & (0x0000ffff);
		flag2 =  Master_Transmitter_Event >> 16;
		last_event = ((I2Cx->SR1 & flag1) | ((I2Cx->SR2 & flag2) << 16) );
		if(last_event == flag)
			bitstatus = Set;
		else
			bitstatus = Reset;
	}
	break;
	}
	return bitstatus ;
}

void I2C_Send_Address (I2C_TypeDef* I2Cx , uint16_t Address , EN_Operation operation) {
	/*
	 * In 7-bit addressing mode,
		– To enter Transmitter mode, a master sends the slave address with LSB reset.
		– To enter Receiver mode, a master sends the slave address with LSB set.
	 */
	Address = (Address << 1) ;
	if (operation == Transmit) {
		Address &= ~(1 << 0) ;
	}
	else {
		Address |= (1 << 0) ;
	}
	I2Cx->DR = Address ;
}

void I2C_Generate_Stop (I2C_TypeDef* I2Cx , EN_Functional_state NewState) {
	if (NewState != disable) {
		I2Cx->CR1 |= I2C_CR1_STOP ;
	}
	else {
		I2Cx->CR1 &= ~(I2C_CR1_STOP) ;
	}
}

void I2C_ACKConfig(I2C_TypeDef *I2Cx, EN_Functional_state NewState) {
	if(NewState == enable) {
		I2Cx->CR1 |= (I2C_CR1_ACK);
	}
	else {
		I2Cx->CR1 &= ~(I2C_CR1_ACK);
	}

}
//===================================================================================================

