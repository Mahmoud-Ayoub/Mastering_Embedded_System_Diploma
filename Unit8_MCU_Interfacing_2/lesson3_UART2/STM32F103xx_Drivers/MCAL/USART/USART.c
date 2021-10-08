/*
 * USART.c
 *
 *      Author: Mahmoud Ayoub
 */
#include "USART.h"

USART_Config_t* g_USART_Cfg[3] = {NULL} ;

/*
 * 		@Fn			-	MCAL_USART_Init
 * 		@brief			-	Initialize USART module
 * 		@param[in]		-	USARTx (USART1 , USART2 , USART3)
 * 						USART configurations required
 * 		@param[out]		-	none
 * 		@return value		-	none
 * 		Note			-	Configuration MACROS can be found in USART.h
 */
void MCAL_USART_Init(USART_TypeDef* USARTx , USART_Config_t* USART_Config) {
	uint32_t pclk ;
	uint32_t BRR_value ;

	// enable USART clock
	if (USARTx == USART1) {
		CLK_EN_USART1() ;
		g_USART_Cfg[0] = USART_Config ;
	}
	else if (USARTx == USART2) {
		CLK_EN_USART2() ;
		g_USART_Cfg[1] = USART_Config ;
	}
	else if (USARTx == USART3) {
		CLK_EN_USART3() ;
		g_USART_Cfg[2] = USART_Config ;
	}

	// enable USART
	USARTx->CR1 |= (1 << 13) ;

	// initialize USART mode
	USARTx->CR1 |= USART_Config->Mode ;

	// initialize USART payload length
	USARTx->CR1 |= USART_Config->PayLoad_Length ;

	// initialize USART parity
	USARTx->CR1 |= USART_Config->Parity ;

	// initialize USART stop bits
	USARTx->CR2 |= USART_Config->StopBits ;

	// initialize USART Hardware flow control
	USARTx->CR3 |= USART_Config->HW_FlowControl ;

	// Baud rate configuration
	if (USARTx == USART1) {
		pclk = MCAL_RCC_Get_PClk2_Freq() ;
	}
	else {
		pclk = MCAL_RCC_Get_PClk1_Freq() ;
	}

	BRR_value = USART_BRR_REG_VALUE(pclk,USART_Config->BaudRate) ;
	USARTx->BRR |= BRR_value ;

	// enable / disable interrupt
	if (USART_Config->IRQ_Enable != USART_IRQ_ENABLE_NONE) {
		USARTx->CR1 |= USART_Config->IRQ_Enable ;

		// enable NVIC
		if (USARTx == USART1){
			NVIC_IRQ37_USART1_ENABLE() ;
		}
		else if (USARTx == USART2) {
			NVIC_IRQ38_USART2_ENABLE() ;
		}
		else if (USARTx == USART3) {
			NVIC_IRQ39_USART3_ENABLE() ;
		}
	}
}

/*
 * 		@Fn			-	MCAL_USART_DeInit
 * 		@brief			-	Reset USART module
 * 		@param[in]		-	USARTx (USART1 , USART2 , USART3)
 * 		@param[out]		-	none
 * 		@return value		-	none
 * 		Note			-	none
 */
void MCAL_USART_DeInit(USART_TypeDef* USARTx) {
	if (USARTx == USART1) {
		USART1_RESET() ;
		NVIC_IRQ37_USART1_DISABLE() ;
	}
	else if (USARTx == USART2) {
		USART2_RESET() ;
		NVIC_IRQ38_USART2_DISABLE() ;
	}
	else if (USARTx == USART3) {
		USART3_RESET() ;
		NVIC_IRQ39_USART3_DISABLE() ;
	}
}

/*
 * 		@Fn			-	MCAL_USART_GPIO_Pins
 * 		@brief			-	Initialize GPIO AF pins for (TX  / RX)
 * 		@param[in]		-	USARTx (USART1 , USART2 , USART3)
 * 		@param[out]		-	none
 * 		@return value		-	none
 * 		Note			-	required AF modes can be found in TRM @ section 9.1.11 GPIO configurations for device peripherals
 *						AFIO pins can be found in TRM @ section 9.3 Alternate function I/O
 */
void MCAL_USART_GPIO_Pins (USART_TypeDef* USARTx) {
	/*
	 * USARTx_TX	Alternate function push-pull
	 * USARTx_RX	Input floating / Input pull-up
	 */
	if (USARTx == USART1) {
		/*
		 * USART1_TX	PA9
		 * USART1_RX	PA10
		 */
		CLK_EN_GPIOA() ;
		CLK_EN_AFIO() ;

		GPIO_PinConfig_t usart_tx_config ;
		usart_tx_config.GPIO_MODE = GPIO_MODE_AF_PUSH_PULL ;
		usart_tx_config .GPIO_Output_Speed = GPIO_SPEED_10M ;
		usart_tx_config .GPIO_PinNumber = GPIO_PIN_9 ;
		MCAL_GPIO_Init(GPIOA, &usart_tx_config) ;

		GPIO_PinConfig_t usart_rx_config ;
		usart_rx_config.GPIO_MODE = GPIO_MODE_INPUT_FLOATING ;
		usart_rx_config.GPIO_PinNumber = GPIO_PIN_10 ;
		MCAL_GPIO_Init(GPIOA, &usart_rx_config) ;
	}
	else if (USARTx == USART2) {
		/*
		 * USART2_TX	PA2
		 * USART2_RX	PA3
		 */
		CLK_EN_GPIOA() ;
		CLK_EN_AFIO() ;

		GPIO_PinConfig_t usart_tx_config ;
		usart_tx_config.GPIO_MODE = GPIO_MODE_AF_PUSH_PULL ;
		usart_tx_config .GPIO_Output_Speed = GPIO_SPEED_10M ;
		usart_tx_config .GPIO_PinNumber = GPIO_PIN_2 ;
		MCAL_GPIO_Init(GPIOA, &usart_tx_config) ;

		GPIO_PinConfig_t usart_rx_config ;
		usart_rx_config.GPIO_MODE = GPIO_MODE_INPUT_FLOATING ;
		usart_rx_config.GPIO_PinNumber = GPIO_PIN_3 ;
		MCAL_GPIO_Init(GPIOA, &usart_rx_config) ;
	}
	else if (USARTx == USART3) {
		/*
		 * USART3_TX	PB10
		 * USART3_RX	PB11
		 */
		CLK_EN_GPIOB() ;
		CLK_EN_AFIO() ;

		GPIO_PinConfig_t usart_tx_config ;
		usart_tx_config.GPIO_MODE = GPIO_MODE_AF_PUSH_PULL ;
		usart_tx_config .GPIO_Output_Speed = GPIO_SPEED_10M ;
		usart_tx_config .GPIO_PinNumber = GPIO_PIN_10 ;
		MCAL_GPIO_Init(GPIOB, &usart_tx_config) ;

		GPIO_PinConfig_t usart_rx_config ;
		usart_rx_config.GPIO_MODE = GPIO_MODE_INPUT_FLOATING ;
		usart_rx_config.GPIO_PinNumber = GPIO_PIN_11 ;
		MCAL_GPIO_Init(GPIOB, &usart_rx_config) ;
	}

}

/*
 * 		@Fn			-	MCAL_USART_Send_Data
 * 		@brief			-	Send Data over UART
 * 		@param[in]		-	USARTx (USART1 , USART2 , USART3)
 * 						pointer to data buffer
 * 						polling mechanism state (enable / disable)
 * 		@param[out]		-	none
 * 		@return value		-	none
 * 		Note			-	none
 */
void MCAL_USART_Send_Data(USART_TypeDef* USARTx , uint16_t* data , EN_Polling_Mechanism polling_state) {

	if (polling_state == enable) {
		// wait for TXE flag to be set
		/*
		 * 	The TXE bit is set by hardware and it indicates:
			• The data has been moved from TDR to the shift register and the data transmission has started.
			• The TDR register is empty.
			• The next data can be written in the USART_DR register without overwriting the previous data.
		 */
		while (!(USARTx->SR & (1 << 7))) ;
	}
	if (USARTx == USART1) {
		if (g_USART_Cfg[0]->PayLoad_Length == USART_PAYLOAD_8B) {
			USARTx->DR = (*data) & (uint8_t)0xFF ;
		}
		else if (g_USART_Cfg[0]->PayLoad_Length == USART_PAYLOAD_9B) {
			USARTx->DR = (*data) & (uint16_t)0x1FF ;
		}
	}
	else if (USARTx == USART2) {
		if (g_USART_Cfg[1]->PayLoad_Length == USART_PAYLOAD_8B) {
			USARTx->DR = (*data) & (uint8_t)0xFF ;
		}
		else if (g_USART_Cfg[1]->PayLoad_Length == USART_PAYLOAD_9B) {
			USARTx->DR = (*data) & (uint16_t)0x1FF ;
		}
	}
	else if (USARTx == USART3) {
		if (g_USART_Cfg[2]->PayLoad_Length == USART_PAYLOAD_8B) {
			USARTx->DR = (*data) & (uint8_t)0xFF ;
		}
		else if (g_USART_Cfg[2]->PayLoad_Length == USART_PAYLOAD_9B) {
			USARTx->DR = (*data) & (uint16_t)0x1FF ;
		}
	}
}

/*
 * 		@Fn			-	MCAL_USART_Receive_Data
 * 		@brief			-	Receive Data over UART
 * 		@param[in]		-	USARTx (USART1 , USART2 , USART3)
 * 						pointer to data buffer
 * 						polling mechanism state (enable / disable)
 * 		@param[out]		-	none
 * 		@return value		-	none
 * 		Note			-	none
 */
void MCAL_USART_Receive_Data(USART_TypeDef* USARTx , uint16_t* data , EN_Polling_Mechanism polling_state) {
	if (polling_state == enable) {
		// wait for RXNE flag to be set
		/*
		 *	It indicates that the content of the shift register is transferred to the RDR.
		 *	In other words, data has been received and can be read
		 */
		while (!(USARTx->SR & (1 << 5))) ;
	}
	if (USARTx == USART1) {
		if (g_USART_Cfg[0]->PayLoad_Length == USART_PAYLOAD_9B) {			// 9 Bits Data
			if (g_USART_Cfg[0]->Parity == USART_PARITY_NONE) {
				// All 9 bits are data
				*data = USARTx->DR ;
			}
			else {
				// just least byte is data
				*data = USARTx->DR & (uint8_t)0xFF ;
			}
		}
		else {										// 8 Bits Data
			if (g_USART_Cfg[0]->Parity == USART_PARITY_NONE) {
				// All 8 bits are data
				*data = USARTx->DR & (uint8_t)0xFF  ;
			}
			else {
				// just least 7 bits are data
				*data = USARTx->DR & (uint8_t)0x7F ;
			}
		}
	}
	else if (USARTx == USART2) {
		if (g_USART_Cfg[1]->PayLoad_Length == USART_PAYLOAD_9B) {			// 9 Bits Data
			if (g_USART_Cfg[1]->Parity == USART_PARITY_NONE) {
				// All 9 bits are data
				*data = USARTx->DR ;
			}
			else {
				// just least byte is data
				*data = USARTx->DR & (uint8_t)0xFF ;
			}
		}
		else {										// 8 Bits Data
			if (g_USART_Cfg[1]->Parity == USART_PARITY_NONE) {
				// All 8 bits are data
				*data = USARTx->DR & (uint8_t)0xFF  ;
			}
			else {
				// just least 7 bits are data
				*data = USARTx->DR & (uint8_t)0x7F ;
			}
		}

	}
	else if (USARTx == USART3) {
		if (g_USART_Cfg[2]->PayLoad_Length == USART_PAYLOAD_9B) {			// 9 Bits Data
			if (g_USART_Cfg[2]->Parity == USART_PARITY_NONE) {
				// All 9 bits are data
				*data = USARTx->DR ;
			}
			else {
				// just least byte is data
				*data = USARTx->DR & (uint8_t)0xFF ;
			}
		}
		else {										// 8 Bits Data
			if (g_USART_Cfg[2]->Parity == USART_PARITY_NONE) {
				// All 8 bits are data
				*data = USARTx->DR & (uint8_t)0xFF  ;
			}
			else {
				// just least 7 bits are data
				*data = USARTx->DR & (uint8_t)0x7F ;
			}
		}
	}
}

//-------------------------------------------ISRs---------------------------------------------------
void USART1_IRQHandler (void) {
	g_USART_Cfg[0]->p_IRQ_CallBack() ;
}
void USART2_IRQHandler (void) {
	g_USART_Cfg[1]->p_IRQ_CallBack() ;
}
void USART3_IRQHandler (void) {
	g_USART_Cfg[2]->p_IRQ_CallBack() ;
}
