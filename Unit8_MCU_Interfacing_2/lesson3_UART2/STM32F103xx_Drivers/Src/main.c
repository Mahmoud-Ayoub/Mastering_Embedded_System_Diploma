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

uint16_t ch ;

void USART1_RX_IRQ_CB (void) {
	MCAL_USART_Receive_Data(USART1, &ch, disable) ;
	MCAL_USART_Send_Data(USART1, &ch, enable) ;
}

int main(void)
{
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
	while (1) {

	}

}
