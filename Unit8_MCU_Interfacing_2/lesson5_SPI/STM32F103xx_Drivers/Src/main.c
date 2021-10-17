/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mahmoud Ayoub
 * @brief          : STM32F103C6
 ******************************************************************************
 */
#include "STM32F103C6.h"
#include "RCC.h"
#include "USART.h"
#include "SPI.h"

/*
 * NOTE : Choose between Master or Slave using the following defined MACROS
 */
#define MCU_MASTER
//#define MCU_SLAVE

uint16_t ch ;

void USART1_RX_IRQ_CB (void) {
#ifdef MCU_MASTER
	MCAL_USART_Receive_Data(USART1, &ch, disable) ;
	MCAL_USART_Send_Data(USART1, &ch, enable) ;

	// send data to SPI
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4 , 0) ;
	MCAL_SPI_Tx_Rx(SPI1, &ch, enable_polling) ;
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4 , 1) ;
#endif
}

void SPI1_IRQ_CB (S_IRQ_SRC irq_src) {
#ifdef MCU_SLAVE
	if (irq_src.RXNE) {
		MCAL_SPI_Receive_Data (SPI1 , &ch , disable_polling) ;
		MCAL_USART_Send_Data (USART1 , &ch , enable) ;
	}
#endif
}

void clock_init (void) {
	CLK_EN_GPIOA() ;
	CLK_EN_GPIOB() ;
}
int main(void)
{
	clock_init() ;

	// ----------------------------------USART init ----------------------------------------------
	USART_Config_t uart1_cfg ;
	uart1_cfg.Mode = USART_MODE_TX_RX ;
	uart1_cfg.BaudRate = USART_BAUDRATE_9600 ;
	uart1_cfg.PayLoad_Length = USART_PAYLOAD_8B ;
	uart1_cfg.Parity = USART_PARITY_NONE ;
	uart1_cfg.StopBits = USART_STOP_BITS_1 ;
	uart1_cfg.HW_FlowControl = USART_FLOWCONTROL_NONE ;
	uart1_cfg.IRQ_Enable = USART_IRQ_ENABLE_RXNE ;
	uart1_cfg.p_IRQ_CallBack = USART1_RX_IRQ_CB ;

	MCAL_USART_Init(USART1, &uart1_cfg) ;
	MCAL_USART_GPIO_Pins(USART1) ;

	// ----------------------------------SPI init ----------------------------------------------
	SPI_Config_t spi1_cfg ;

	// common configurations
	spi1_cfg.Communication_Modes = SPI_Direction_2LINES ;
	spi1_cfg.Clk_Phase = SPI_CLK_PHASE_SECOND_EDGE ;
	spi1_cfg.Clk_Polarity = SPI_CLK_POLARITY_HIGH_IDLE ;
	spi1_cfg.Data_Size = SPI_DATA_SIZE_8_BITS ;
	spi1_cfg.Frame_Format = SPI_FRAME_FORMAT_MSB_FIRST ;
	spi1_cfg.Clk_Freq = SPI_CLK_PRESCALER_8 ;

#ifdef MCU_MASTER
	spi1_cfg.Device_Mode = SPI_MASTER_MODE ;
	spi1_cfg.IRQ_Enable = SPI_IRQ_ENABLE_NONE ;
	spi1_cfg.NSS = SPI_NSS_SLAVE_SW_SET ;
	spi1_cfg.p_IRQ_CallBack = NULL ;
#endif

#ifdef MCU_SLAVE
	spi1_cfg.Device_Mode = SPI_SLAVE_MODE ;
	spi1_cfg.NSS = SPI_NSS_HW_SLAVE ;
	spi1_cfg.IRQ_Enable = SPI_IRQ_ENABLE_RXNE ;
	spi1_cfg.p_IRQ_CallBack = SPI1_IRQ_CB ;
#endif

	// configure SS pin on PA4 by GPIO
	GPIO_PinConfig_t ss_pin_cfg ;
	ss_pin_cfg.GPIO_PinNumber = GPIO_PIN_4 ;
	ss_pin_cfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSH_PULL ;
	ss_pin_cfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(GPIOA, &ss_pin_cfg) ;
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4 , 1) ;

	MCAL_SPI_Init(SPI1, &spi1_cfg) ;
	MCAL_SPI_GPIO_Pins(SPI1) ;

	while (1) {

	}

}
