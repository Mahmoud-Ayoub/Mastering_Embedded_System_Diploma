/*
 * USART.h
 *
 *      Author: Mahmoud Ayoub
 */

#ifndef INC_USART_H_
#define INC_USART_H_

#include "STM32F103C6.h"
#include "RCC.h"
#include "GPIO.h"

typedef struct {
	uint8_t Mode ;          		        // specifies RX / TX Mode
											// This parameter is set from @ref USART_MODE @ USART.h

	uint32_t BaudRate ;						// specifies required baud rate
											// This parameter is set from @ref USART_BAUDRATE @ USART.h

	uint16_t PayLoad_Length ;				// specifies required data length (8 bits / 9 bits)
											// This parameter is set from @ref USART_PAYLOAD_LENGTH @ USART.h

	uint16_t Parity ; 						// specifies required parity (even / odd / none)
											// This parameter is set from @ref USART_PARITY @ USART.h

	uint16_t StopBits ; 					// specifies required number of stop bits (1 / 2)
											// This parameter is set from @ref USART_STOPBITS @ USART.h

	uint16_t HW_FlowControl ; 				// specified required flow control (enabled / disabled)
											// This parameter is set from @ref USART_HW_FLOW_CONTROL @ USART.h

	uint16_t IRQ_Enable ; 					// specifies interrupt status flags (enabled / disabled)
											// This parameter is set form @ref USART_IRQ_STATUS	@ref USART.h

	void(*p_IRQ_CallBack)(void) ; 			// pointer to callback function needed to be executed in app when IRQ happens

}USART_Config_t;

typedef enum {
	disable ,
	enable
}EN_Polling_Mechanism;

// ---------------------------------Reference MACROS ------------------------------------------------

// @ref USART_MODE
#define USART_MODE_RX						((uint8_t)(1 << 2))
#define USART_MODE_TX						((uint8_t)(1 << 3))
#define USART_MODE_TX_RX					((uint8_t)((1 << 2) | (1 << 3)))

// @ref USART_BAUDRATE
#define USART_BAUDRATE_2400					2400
#define USART_BAUDRATE_9600					9600
#define USART_BAUDRATE_19200				19200
#define USART_BAUDRATE_57600				57600
#define USART_BAUDRATE_115200				115200
#define USART_BAUDRATE_230400				230400
#define USART_BAUDRATE_460800				460800
#define USART_BAUDRATE_921600				921600
#define USART_BAUDRATE_2250000				2250000
#define USART_BAUDRATE_4500000				4500000

// @ref USART_PAYLOAD_LENGTH
#define USART_PAYLOAD_8B					((uint32_t)(0 << 12))
#define USART_PAYLOAD_9B					((uint32_t)(1 << 12))

// @ref USART_PARITY
#define USART_PARITY_NONE					((uint32_t)(0 << 10))
#define USART_PARITY_EVEN					((uint32_t)((1 << 10) | (0 << 9)))
#define USART_PARITY_ODD					((uint32_t)((1 << 10) | (1 << 9)))

// @ref USART_STOPBITS
#define USART_STOP_BITS_HALF				((uint32_t)(0b01 << 12))
#define USART_STOP_BITS_1					((uint32_t)(0b00 << 12))
#define USART_STOP_BITS_1_HALF				((uint32_t)(0b11 << 12))
#define USART_STOP_BITS_2					((uint32_t)(0b10 << 12))

// @ref USART_HW_FLOW_CONTROL
#define USART_FLOWCONTROL_NONE				((uint32_t)(0b00 << 8))
#define USART_FLOWCONTROL_CTS				((uint32_t)(0b10 << 8))
#define USART_FLOWCONTROL_RTS				((uint32_t)(0b01 << 8))
#define USART_FLOWCONTROL_CTS_RTS			((uint32_t)(0b11 << 8))

// @ref USART_IRQ_STATUS
#define USART_IRQ_ENABLE_NONE				((uint32_t)(0))
#define USART_IRQ_ENABLE_TXE				((uint32_t)(1 << 7))
#define USART_IRQ_ENABLE_CTS				((uint32_t)(1 << 10))
#define USART_IRQ_ENABLE_TC					((uint32_t)(1 << 6))
#define USART_IRQ_ENABLE_RXNE				((uint32_t)(1 << 5))
#define USART_IRQ_ENABLE_IDLE				((uint32_t)(1 << 4))
#define USART_IRQ_ENABLE_PE					((uint32_t)(1 << 8))


// ---------------------------------BAUD RATE Calculations MACROS -------------------------------------------
#define USARTDIV(PCLK,BAUD)					(uint32_t)((PCLK) / (16 * BAUD))
#define	MANTISSA(PCLK,BAUD)					(uint32_t)((PCLK) / (16 * BAUD))
#define USARTDIV_100(PCLK,BAUD)				(uint32_t)((25 * PCLK) / (4 * BAUD))
#define	MANTISSA_100(PCLK,BAUD)				(uint32_t)((MANTISSA(PCLK,BAUD))*100)
#define FRACTION(PCLK,BAUD)					(uint32_t)((( USARTDIV_100(PCLK,BAUD) - MANTISSA_100(PCLK,BAUD) ) * 16 ) / 100 )
#define USART_BRR_REG_VALUE(PCLK,BAUD)		(((MANTISSA(PCLK,BAUD)) << 4 ) | ((FRACTION(PCLK,BAUD)) & 0xF))

// ---------------------------------APIs ------------------------------------------------
void MCAL_USART_Init(USART_TypeDef* USARTx , USART_Config_t* USART_Config) ;
void MCAL_USART_DeInit(USART_TypeDef* USARTx) ;
void MCAL_USART_GPIO_Pins (USART_TypeDef* USARTx) ;
void MCAL_USART_Send_Data(USART_TypeDef* USARTx , uint16_t* data , EN_Polling_Mechanism polling_state) ;
void MCAL_USART_Receive_Data(USART_TypeDef* USARTx , uint16_t* data , EN_Polling_Mechanism polling_state) ;

#endif /* INC_USART_H_ */
