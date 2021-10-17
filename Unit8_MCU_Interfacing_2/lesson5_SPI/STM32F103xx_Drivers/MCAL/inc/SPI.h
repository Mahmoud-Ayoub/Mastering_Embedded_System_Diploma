/*
 * SPI.h
 *
 *      Author: Mahmoud Ayoub
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "STM32F103C6.h"
#include "RCC.h"
#include "GPIO.h"

typedef struct {
	uint8_t TXE 	 : 1 ;
	uint8_t RXNE 	 : 1 ;
	uint8_t ERRI 	 : 1 ;
	uint8_t Reserved : 5 ;
}S_IRQ_SRC;

typedef struct {
	// specifies master mode / slave mode
	// This parameter is set from @ref SPI_DEVICE_MODE @ SPI.h
	uint8_t Device_Mode ;

	// specifies full duplex / half duplex / simplex communication mode
	// This parameter is set from @ref SPI_COMMUNICATION_MODE @ SPI.h
	uint16_t Communication_Modes ;

	// specifies 8 bits data / 16 bits data
	// This parameter is set from @ref SPI_DATA_SIZE @ SPI.h
	uint16_t Data_Size ;

	// specifies sent bit first LSB / MSB
	// This parameter is set from @ref SPI_FRAME_FORMAT @ SPI.h
	uint8_t Frame_Format ;

	// specifies idle state of clock 0 / 1 when idle
	// This parameter is set from @ref SPI_CLK_POLARITY @ SPI.h
	uint8_t Clk_Polarity ;

	// specifies capturing edge first edge / second edge
	// This parameter is set from @ref SPI_CLK_PHASE @ SPI.h
	uint8_t Clk_Phase ;

	// specifies NSS management
	// This parameter is set from @ref SPI_NSS @ SPI.h
	uint16_t NSS ;

	// specifies clock frequency depending on prescaler determined
	// This parameter is set from @ref SPI_CLK_FREQ @ SPI.h
	uint8_t Clk_Freq ;

	// specifies interrupt status flags (enabled / disabled)
	// This parameter is set form @ref SPI_IRQ_STATUS @ SPI.h
	uint8_t IRQ_Enable ;

	// pointer to callback function needed to be executed in app when IRQ happens
	void(*p_IRQ_CallBack)(S_IRQ_SRC irq_src) ;


}SPI_Config_t;

typedef enum {
	disable_polling ,
	enable_polling
}EN_Polling;

// ---------------------------------Reference MACROS ------------------------------------------------

// @ref SPI_DEVICE_MODE
#define SPI_MASTER_MODE					((uint8_t)(1 << 2))
#define SPI_SLAVE_MODE					(0x00000000U)

// @ref SPI_COMMUNICATION_MODE
#define SPI_Direction_2LINES			(0x00000000U)
#define SPI_Direction_2LINES_RXONLY		((uint16_t)(1 << 10))
#define SPI_Direction_1LINE_RXONLY		((uint16_t)(1 << 15))
#define SPI_Direction_1LINE_TXONLY		((uint16_t)((1 << 15) | (1 << 14)))

// @ref SPI_DATA_SIZE
#define SPI_DATA_SIZE_8_BITS			(0x00000000U)
#define SPI_DATA_SIZE_16_BITS			((uint16_t)(1 << 11))

// @ref SPI_FRAME_FORMAT
#define SPI_FRAME_FORMAT_LSB_FIRST		((uint8_t)(1 << 7))
#define SPI_FRAME_FORMAT_MSB_FIRST		((uint8_t)(0 << 7))

// @ref SPI_CLK_POLARITY
#define SPI_CLK_POLARITY_HIGH_IDLE		((uint8_t)(1 << 1))
#define SPI_CLK_POLARITY_LOW_IDLE		((uint8_t)(0 << 1))

// @ref SPI_CLK_PHASE
#define SPI_CLK_PHASE_FIRST_EDGE		((uint8_t)(0 << 0))
#define SPI_CLK_PHASE_SECOND_EDGE		((uint8_t)(1 << 0))

// @ref SPI_NSS
#define SPI_NSS_SLAVE_SW_SET				((uint16_t)((1 << 9) | (1 << 8)))		// SSM in CR1
#define SPI_NSS_SLAVE_SW_RESET				((uint16_t)(1 << 9))					// SSM in CR1
#define SPI_NSS_HW_SLAVE					(0x00000000U)
#define SPI_NSS_HW_MASTER_OUTPUT_ENABLE		((uint16_t)(1 << 2))					// SSOE in CR2
#define SPI_NSS_HW_MASTER_OUTPUT_DISABLE	(~(uint16_t)(1 << 2))					// SSOE in CR2

// @ref SPI_CLK_FREQ
/*
000: fPCLK/2
001: fPCLK/4
010: fPCLK/8
011: fPCLK/16
100: fPCLK/32
101: fPCLK/64
110: fPCLK/128
111: fPCLK/256
*/
#define SPI_CLK_PRESCALER_2				((uint8_t)(0b000 << 3))
#define SPI_CLK_PRESCALER_4				((uint8_t)(0b001 << 3))
#define SPI_CLK_PRESCALER_8				((uint8_t)(0b010 << 3))
#define SPI_CLK_PRESCALER_16			((uint8_t)(0b011 << 3))
#define SPI_CLK_PRESCALER_32			((uint8_t)(0b100 << 3))
#define SPI_CLK_PRESCALER_64			((uint8_t)(0b101 << 3))
#define SPI_CLK_PRESCALER_128			((uint8_t)(0b110 << 3))
#define SPI_CLK_PRESCALER_256			((uint8_t)(0b111 << 3))

// @ref SPI_IRQ_STATUS
#define SPI_IRQ_ENABLE_NONE			((uint8_t)(0))
#define SPI_IRQ_ENABLE_TXE			((uint8_t)(1 << 7))
#define SPI_IRQ_ENABLE_RXNE			((uint8_t)(1 << 6))
#define SPI_IRQ_ENABLE_ERR			((uint8_t)(1 << 5))



// ---------------------------------Generic Flags ------------------------------------------------
#define SPE_BIT		6
#define TXE_BIT		1
#define RXNE_BIT	0
#define ERROR_BIT	4

// ---------------------------------APIs ------------------------------------------------
void MCAL_SPI_Init (SPI_TypeDef* SPIx , SPI_Config_t* SPI_Cfg) ;
void MCAL_SPI_DeInit (SPI_TypeDef* SPIx) ;
void MCAL_SPI_GPIO_Pins (SPI_TypeDef* SPIx) ;
void MCAL_SPI_Send_Data (SPI_TypeDef* SPIx , uint16_t* data_buffer , EN_Polling polling_state) ;
void MCAL_SPI_Receive_Data (SPI_TypeDef* SPIx , uint16_t* data_buffer , EN_Polling polling_state) ;
void MCAL_SPI_Tx_Rx (SPI_TypeDef* SPIx , uint16_t* data_buffer , EN_Polling polling_state) ;

#endif /* INC_SPI_H_ */
