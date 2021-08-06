#include <stdint.h>
#define Start_SP 0x20001000
extern int main (void) ; 
extern uint32_t _S_DATA ; 
extern uint32_t _E_DATA ; 
extern uint32_t _S_BSS ; 
extern uint32_t _E_BSS ; 
extern uint32_t _E_text ;
extern _stack_top ;  

void Reset_Handler (void) {
	// Copy .data section from flash to SRAM
	unsigned int DATA_size = (unsigned char *) &_E_DATA - (unsigned char *) &_S_DATA ; 
	unsigned char * P_src = (unsigned char *) &_E_text ; 
	unsigned char * P_dst = (unsigned char *) &_S_DATA ; 
	for (int i = 0 ; i < DATA_size ; i++) {
		*((unsigned char *) P_dst++) = *((unsigned char *) P_src++) ; 
	}

	// initialize .bss section with zero
	unsigned int BSS_size = (unsigned char *) &_E_BSS - (unsigned char *) &_S_BSS ;
	P_dst = (unsigned char *) &_S_BSS ;
	for (int i = 0 ; i < BSS_size ; i++) {
		*((unsigned char *) P_dst++) =  (unsigned char) 0 ; 
	}

	main() ; 
}
void NMI_Handler (void) {
	Reset_Handler() ; 
}
void MM_Fault_Handler (void) {
	Reset_Handler() ; 
}
void Bus_Fault_Handler (void) {
	Reset_Handler() ; 
}

uint32_t vectors [] __attribute__ ((section(".vectors"))) = {
	(uint32_t) &_stack_top ,
	(uint32_t) &Reset_Handler , 
	(uint32_t) &NMI_Handler , 
	(uint32_t) &MM_Fault_Handler , 
	(uint32_t) &Bus_Fault_Handler , 
} ; 
