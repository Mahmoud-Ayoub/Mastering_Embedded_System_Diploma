/*
 * EXTI_ATmega32.c
 *
 * Author : Mahmoud Ayoub
 */ 

#include <util/delay.h>
#include <avr/interrupt.h>
#include "Bit_Math.h"

#define SREG_REG	(*((volatile unsigned char*)0x5F))
#define GICR_REG	(*((volatile unsigned char*)0x5B))
#define GIFR_REG	(*((volatile unsigned char*)0x5A))
#define MCUCR_REG	(*((volatile unsigned char*)0x55))
#define MCUCSR_REG	(*((volatile unsigned char*)0x54))
#define DDRB_REG	(*((volatile unsigned char*)0x37))
#define PORTB_REG	(*((volatile unsigned char*)0x38))
#define DDRD_REG	(*((volatile unsigned char*)0x31))
#define PORTD_REG	(*((volatile unsigned char*)0x32))

void EXTI0_init (void) {
	CLEAR_BIT (DDRD_REG , 2) ;              // configure PD2 (EXTI0) as an input
	MCUCR_REG |= (0b01 << 0) ;              // configure Any logical change on INT0 generates an interrupt request
	SET_BIT (GICR_REG , 6) ;                // enable EXTI0
}
void EXTI1_init (void) {
	CLEAR_BIT (DDRD_REG , 3) ;              // configure PD3 (EXTI1) as an input
	MCUCR_REG |= (0b11 << 2) ;              // configure The rising edge of INT1 generates an interrupt request
	SET_BIT (GICR_REG , 7) ;                // enable EXTI1
}
void EXTI2_init (void) {
	CLEAR_BIT (DDRB_REG , 2) ;              // configure PB2 (EXTI2) as an input
										//  If ISC2 is written to zero, a falling edge on INT2 activates the interrupt
	CLEAR_BIT (MCUCSR_REG , 6) ;            // configure The falling edge of INT2 generates an interrupt request 
	SET_BIT (GICR_REG , 5) ;                // enable EXTI2
}
void LEDs_init (void) {
	SET_BIT (DDRD_REG , 5) ;                // configure PD5 (LED0) as an output 
	SET_BIT (DDRD_REG , 6) ;                // configure PD6 (LED1) as an output 
	SET_BIT (DDRD_REG , 7) ;                // configure PD7 (LED2) as an output 
}
void GI_enable (void) {
	SET_BIT (SREG_REG , 7) ;                // enable global interrupt
}

int main(void)
{	 
	EXTI0_init() ; 
	EXTI1_init() ;
	EXTI2_init() ; 
	LEDs_init() ; 
	GI_enable() ; 
	 
    while (1) 
    {
		CLEAR_BIT (PORTD_REG , 5) ;
		CLEAR_BIT (PORTD_REG , 6) ;  
		CLEAR_BIT (PORTD_REG , 7) ;  
    }
}
ISR (INT0_vect) {
	TOGGLE_BIT (PORTD_REG , 5) ; 
	_delay_ms(1000) ; 
}
ISR (INT1_vect) {
	TOGGLE_BIT (PORTD_REG , 6) ;
	_delay_ms(1000) ;
}
ISR (INT2_vect) {
	TOGGLE_BIT (PORTD_REG , 7) ;
	_delay_ms(1000) ;
}

