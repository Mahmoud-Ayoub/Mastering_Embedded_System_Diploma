/*
 * SPI.c
 *
 *      Author: Mahmoud Ayoub
 */
#include "SPI.h"
// ---------------------------------Global Variables ------------------------------------------------
SPI_Config_t* g_SPI_Cfg[2] = {NULL , NULL} ;
SPI_Config_t g_SPI_Cfg1 ;
SPI_Config_t g_SPI_Cfg2 ;
// ---------------------------------Generic MACROS ------------------------------------------------
#define SPI1_index	0
#define SPI2_index	1


// ---------------------------------APIs ------------------------------------------------

/*
 * 		@Fn				-	MCAL_SPI_Init
 * 		@brief			-	Initialize SPI module
 * 		@param[in]		-	SPIx (SPI1 , SPI2)
 * 						 	SPIx configurations required
 * 		@param[out]		-	none
 * 		@return value	-	none
 * 		Note			-	Configuration MACROS can be found in SPI.h
 */
void MCAL_SPI_Init (SPI_TypeDef* SPIx , SPI_Config_t* SPI_Cfg) {
	uint32_t tempCR1_reg = 0 ;
	uint32_t tempCR2_reg = 0 ;

	if (SPIx == SPI1) {
		CLK_EN_SPI1() ;
		g_SPI_Cfg1 = *SPI_Cfg ;
		g_SPI_Cfg[SPI1_index] = &g_SPI_Cfg1 ;
	}
	else if (SPIx == SPI2) {
		CLK_EN_SPI2() ;
		g_SPI_Cfg2 = *SPI_Cfg ;
		g_SPI_Cfg[SPI2_index] = &g_SPI_Cfg2 ;
	}
	tempCR1_reg |= (1 << SPE_BIT) ; 				// SPE enable
	tempCR1_reg |= SPI_Cfg->Device_Mode ;
	tempCR1_reg |= SPI_Cfg->Communication_Modes ;
	tempCR1_reg |= SPI_Cfg->Data_Size ;
	tempCR1_reg |= SPI_Cfg->Clk_Polarity ;
	tempCR1_reg |= SPI_Cfg->Clk_Phase ;
	tempCR1_reg |= SPI_Cfg->Frame_Format ;
	if (SPI_Cfg->NSS == SPI_NSS_HW_MASTER_OUTPUT_ENABLE) {
		tempCR2_reg |= SPI_Cfg->NSS ;
	}
	else if (SPI_Cfg->NSS == SPI_NSS_HW_MASTER_OUTPUT_DISABLE) {
		tempCR2_reg &= SPI_Cfg->NSS ;
	}
	else {
		tempCR1_reg |= SPI_Cfg->NSS ;
	}

	tempCR1_reg |= SPI_Cfg->Clk_Freq ;

	if (SPI_Cfg->IRQ_Enable != SPI_IRQ_ENABLE_NONE) {
		tempCR2_reg |= SPI_Cfg->IRQ_Enable ;
		if (SPIx == SPI1) {
			NVIC_IRQ35_SPI1_ENABLE() ;
		}
		else if (SPIx == SPI2) {
			NVIC_IRQ36_SPI2_ENABLE() ;
		}
	}
	SPIx->CR1 = tempCR1_reg ;
	SPIx->CR2 = tempCR2_reg ;
}

/*
 * 		@Fn				-	MCAL_SPI_DeInit
 * 		@brief			-	Reset SPI module
 * 		@param[in]		-	SPIx (SPI1 , SPI2)
 * 		@param[out]		-	none
 * 		@return value	-	none
 * 		Note			-	none
 */
void MCAL_SPI_DeInit (SPI_TypeDef* SPIx) {
	if (SPIx == SPI1) {
		SPI1_RESET() ;
		NVIC_IRQ35_SPI1_DISABLE() ;
	}
	else if (SPIx == SPI2) {
		SPI2_RESET() ;
		NVIC_IRQ36_SPI2_DISABLE() ;
	}
}

/*
 * 		@Fn				-	MCAL_SPI_GPIO_Pins
 * 		@brief			-	Initialize GPIO AF pins for (MOSI  / MISO / SCK / SS)
 * 		@param[in]		-	SPIx (SPI1 , SPI2)
 * 		@param[out]		-	none
 * 		@return value	-	none
 * 		Note			-	required AF modes can be found in TRM @ section 9.1.11 GPIO configurations for device peripherals
 *							AFIO pins can be found in TRM @ section 9.3 Alternate function I/O
 */
void MCAL_SPI_GPIO_Pins (SPI_TypeDef* SPIx) {
	GPIO_PinConfig_t pin_config ;
	if (SPIx == SPI1) {
		/*
			SPI1_NSS 	PA4
			SPI1_SCK 	PA5
			SPI1_MISO 	PA6
			SPI1_MOSI	PA7
		 */
		if (g_SPI_Cfg[SPI1_index]->Device_Mode == SPI_MASTER_MODE) {
			// MASTER
			/*
			SPI1_NSS 	PA4		Hardware master /slave >> Input floating/ Input pull-up / Input pull-down
								Hardware master/ NSS output enabled >> Alternate function push-pull
								Software >> Not used. Can be used as a GPIO
			SPI1_SCK 	PA5		Alternate function push-pull
			SPI1_MISO 	PA6		Input floating / Input pull-up
			SPI1_MOSI	PA7		Alternate function push-pull
			 */

			// SPI1_NSS
			switch (g_SPI_Cfg[SPI1_index]->NSS) {
			case SPI_NSS_HW_MASTER_OUTPUT_DISABLE :
				pin_config.GPIO_MODE = GPIO_MODE_INPUT_FLOATING ;
				pin_config.GPIO_PinNumber = GPIO_PIN_4 ;
				MCAL_GPIO_Init (GPIOA, &pin_config) ;
				break ;

			case SPI_NSS_HW_MASTER_OUTPUT_ENABLE :
				pin_config.GPIO_MODE = GPIO_MODE_AF_PUSH_PULL ;
				pin_config.GPIO_PinNumber = GPIO_PIN_4 ;
				pin_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
				MCAL_GPIO_Init (GPIOA, &pin_config) ;
				break ;
			}

			// SPI1_SCK
			pin_config.GPIO_MODE = GPIO_MODE_AF_PUSH_PULL ;
			pin_config.GPIO_PinNumber = GPIO_PIN_5 ;
			pin_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init (GPIOA, &pin_config) ;

			// SPI1_MISO
			pin_config.GPIO_MODE = GPIO_MODE_INPUT_FLOATING ;
			pin_config.GPIO_PinNumber = GPIO_PIN_6 ;
			MCAL_GPIO_Init (GPIOA, &pin_config) ;

			// SPI1_MOSI
			pin_config.GPIO_MODE = GPIO_MODE_AF_PUSH_PULL ;
			pin_config.GPIO_PinNumber = GPIO_PIN_7 ;
			pin_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init (GPIOA, &pin_config) ;
		}
		else {
			// SLAVE
			/*
			SPI1_NSS 	PA4		Hardware master /slave >> Input floating/ Input pull-up / Input pull-down
								Hardware master/ NSS output enabled >> Alternate function push-pull
								Software >> Not used. Can be used as a GPIO
			SPI1_SCK 	PA5		Input floating
			SPI1_MISO 	PA6		Alternate function push-pull
			SPI1_MOSI	PA7		Input floating / Input pull-up
			 */

			// SPI1_NSS
			if (g_SPI_Cfg[SPI1_index]->NSS == SPI_NSS_HW_SLAVE) {
				pin_config.GPIO_MODE = GPIO_MODE_INPUT_FLOATING ;
				pin_config.GPIO_PinNumber = GPIO_PIN_4 ;
				MCAL_GPIO_Init (GPIOA, &pin_config) ;
			}

			// SPI1_SCK
			pin_config.GPIO_MODE = GPIO_MODE_INPUT_FLOATING ;
			pin_config.GPIO_PinNumber = GPIO_PIN_5 ;
			MCAL_GPIO_Init (GPIOA, &pin_config) ;

			// SPI1_MISO
			pin_config.GPIO_MODE = GPIO_MODE_AF_PUSH_PULL ;
			pin_config.GPIO_PinNumber = GPIO_PIN_6 ;
			pin_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init (GPIOA, &pin_config) ;

			// SPI1_MOSI
			pin_config.GPIO_MODE = GPIO_MODE_INPUT_FLOATING ;
			pin_config.GPIO_PinNumber = GPIO_PIN_7 ;
			MCAL_GPIO_Init (GPIOA, &pin_config) ;
		}

	}
	else if (SPIx == SPI2) {
		/*
			SPI2_NSS 	PB12
			SPI2_SCK 	PB13
			SPI2_MISO 	PB14
			SPI2_MOSI	PB15
		 */
		if (g_SPI_Cfg[SPI2_index]->Device_Mode == SPI_MASTER_MODE) {
			// MASTER
			/*
					SPI2_NSS 	PB12		Hardware master /slave >> Input floating/ Input pull-up / Input pull-down
											Hardware master/ NSS output enabled >> Alternate function push-pull
											Software >> Not used. Can be used as a GPIO
					SPI2_SCK 	PB13		Alternate function push-pull
					SPI1_MISO 	PB14		Input floating / Input pull-up
					SPI1_MOSI	PB15		Alternate function push-pull
			 */

			// SPI2_NSS
			switch (g_SPI_Cfg[SPI2_index]->NSS) {
			case SPI_NSS_HW_MASTER_OUTPUT_DISABLE :
				pin_config.GPIO_MODE = GPIO_MODE_INPUT_FLOATING ;
				pin_config.GPIO_PinNumber = GPIO_PIN_12 ;
				MCAL_GPIO_Init (GPIOB, &pin_config) ;
				break ;

			case SPI_NSS_HW_MASTER_OUTPUT_ENABLE :
				pin_config.GPIO_MODE = GPIO_MODE_AF_PUSH_PULL ;
				pin_config.GPIO_PinNumber = GPIO_PIN_12 ;
				pin_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
				MCAL_GPIO_Init (GPIOB, &pin_config) ;
				break ;
			}

			// SPI2_SCK
			pin_config.GPIO_MODE = GPIO_MODE_AF_PUSH_PULL ;
			pin_config.GPIO_PinNumber = GPIO_PIN_13 ;
			pin_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init (GPIOB, &pin_config) ;

			// SPI2_MISO
			pin_config.GPIO_MODE = GPIO_MODE_INPUT_FLOATING ;
			pin_config.GPIO_PinNumber = GPIO_PIN_14 ;
			MCAL_GPIO_Init (GPIOB, &pin_config) ;

			// SPI2_MOSI
			pin_config.GPIO_MODE = GPIO_MODE_AF_PUSH_PULL ;
			pin_config.GPIO_PinNumber = GPIO_PIN_15 ;
			pin_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init (GPIOB, &pin_config) ;
		}
		else {
			// SLAVE
			/*
					SPI2_NSS 	PB12		Hardware master /slave >> Input floating/ Input pull-up / Input pull-down
											Hardware master/ NSS output enabled >> Alternate function push-pull
											Software >> Not used. Can be used as a GPIO
					SPI2_SCK 	PB13		Input floating
					SPI2_MISO 	PB14		Alternate function push-pull
					SPI2_MOSI	PB15		Input floating / Input pull-up
			 */

			// SPI2_NSS
			if (g_SPI_Cfg[SPI1_index]->NSS == SPI_NSS_HW_SLAVE) {
				pin_config.GPIO_MODE = GPIO_MODE_INPUT_FLOATING ;
				pin_config.GPIO_PinNumber = GPIO_PIN_12 ;
				MCAL_GPIO_Init (GPIOB, &pin_config) ;
			}

			// SPI2_SCK
			pin_config.GPIO_MODE = GPIO_MODE_INPUT_FLOATING ;
			pin_config.GPIO_PinNumber = GPIO_PIN_13 ;
			MCAL_GPIO_Init (GPIOB, &pin_config) ;

			// SPI2_MISO
			pin_config.GPIO_MODE = GPIO_MODE_AF_PUSH_PULL ;
			pin_config.GPIO_PinNumber = GPIO_PIN_14 ;
			pin_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init (GPIOB, &pin_config) ;

			// SPI2_MOSI
			pin_config.GPIO_MODE = GPIO_MODE_INPUT_FLOATING ;
			pin_config.GPIO_PinNumber = GPIO_PIN_15 ;
			MCAL_GPIO_Init (GPIOB, &pin_config) ;
		}
	}

}

/*
 * 		@Fn				-	MCAL_SPI_Send_Data
 * 		@brief			-	Send Data over SPI
 * 		@param[in]		-	SPIx (SPI1 , SPI2)
 * 							pointer to data buffer
 * 							polling mechanism state (enable / disable)
 * 		@param[out]		-	none
 * 		@return value	-	none
 * 		Note			-	none
 */
void MCAL_SPI_Send_Data (SPI_TypeDef* SPIx , uint16_t* data_buffer , EN_Polling polling_state) {
	if (polling_state == enable_polling) {
		/*
		 *  TXE: Transmit buffer empty
			0: Tx buffer not empty
			1: Tx buffer empty
		 */
		while (!(SPIx->SR & (1 << TXE_BIT))) ;
	}
	SPIx->DR = *data_buffer ;
}

/*
 * 		@Fn				-	MCAL_SPI_Receive_Data
 * 		@brief			-	Receive Data over SPI
 * 		@param[in]		-	SPIx (SPI1 , SPI2)
 * 							pointer to data buffer
 * 							polling mechanism state (enable / disable)
 * 		@param[out]		-	none
 * 		@return value	-	none
 * 		Note			-	none
 */
void MCAL_SPI_Receive_Data (SPI_TypeDef* SPIx , uint16_t* data_buffer , EN_Polling polling_state) {
	if (polling_state == enable_polling) {
		/*
		 *  RXNE: Receive buffer not empty
			0: Rx buffer empty
			1: Rx buffer not empty
		 */
		while (!(SPIx->SR & (1 << RXNE_BIT))) ;
	}
	*data_buffer = SPIx->DR ;
}

/*
 * 		@Fn				-	MCAL_SPI_Tx_Rx
 * 		@brief			-	Transmit and Receive Data over SPI
 * 		@param[in]		-	SPIx (SPI1 , SPI2)
 * 							pointer to data buffer
 * 							polling mechanism state (enable / disable)
 * 		@param[out]		-	none
 * 		@return value	-	none
 * 		Note			-	none
 */
void MCAL_SPI_Tx_Rx (SPI_TypeDef* SPIx , uint16_t* data_buffer , EN_Polling polling_state) {
	if (polling_state == enable_polling) {
		/*
		 *  TXE: Transmit buffer empty
				0: Tx buffer not empty
				1: Tx buffer empty
		 */
		while (!(SPIx->SR & (1 << TXE_BIT))) ;
	}
	SPIx->DR = *data_buffer ;

	if (polling_state == enable_polling) {
		/*
		 *  RXNE: Receive buffer not empty
					0: Rx buffer empty
					1: Rx buffer not empty
		 */
		while (!(SPIx->SR & (1 << RXNE_BIT))) ;
	}
	*data_buffer = SPIx->DR ;
}

//-------------------------------------------ISRs---------------------------------------------------
void SPI1_IRQHandler (void) {
	S_IRQ_SRC irq_src ;
	irq_src.TXE = ( (SPI1->SR & (1 << TXE_BIT)) >> TXE_BIT ) ;
	irq_src.RXNE = ( (SPI1->SR & (1 << RXNE_BIT)) >> RXNE_BIT ) ;
	irq_src.ERRI = ( (SPI1->SR & (1 << ERROR_BIT)) >> ERROR_BIT ) ;
	g_SPI_Cfg[SPI1_index]->p_IRQ_CallBack(irq_src) ;
}

void SPI2_IRQHandler (void) {
	S_IRQ_SRC irq_src ;
	irq_src.TXE = ( (SPI2->SR & (1 << TXE_BIT)) >> TXE_BIT ) ;
	irq_src.RXNE = ( (SPI2->SR & (1 << RXNE_BIT)) >> RXNE_BIT ) ;
	irq_src.ERRI = ( (SPI2->SR & (1 << ERROR_BIT)) >> ERROR_BIT ) ;
	g_SPI_Cfg[SPI2_index]->p_IRQ_CallBack(irq_src) ;

}
