#include <stdint.h>
#define Start_SP 0x20001000
extern int main (void) ; 
void Reset_Handler (void) {
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
	(uint32_t) Start_SP ,
	(uint32_t) &Reset_Handler , 
	(uint32_t) &NMI_Handler , 
	(uint32_t) &MM_Fault_Handler , 
	(uint32_t) &Bus_Fault_Handler , 
} ; 
