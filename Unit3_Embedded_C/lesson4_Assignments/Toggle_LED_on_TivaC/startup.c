#include <stdint.h>
#define Start_SP 0x20001000
extern int main (void) ; 
extern uint32_t _S_DATA ; 
extern uint32_t _E_DATA ; 
extern uint32_t _S_BSS ; 
extern uint32_t _E_BSS ; 
extern uint32_t _E_text ; 
 
static unsigned int stack_top [256] ; /* Booking 1024 Bytes in .bss through uninitialized array of 256 int (256*4=1024) */

void Reset_Handler () {
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
void NMI_Handler () {
	Reset_Handler() ; 
}
void MM_Fault_Handler () {
	Reset_Handler() ; 
}
void Bus_Fault_Handler () {
	Reset_Handler() ; 
}

void (*const g_p_fn_Vectors[]) () __attribute__ ((section(".vectors"))) = {        // array of pointers to functions
	(void (*) ()) (&stack_top[0]+sizeof(stack_top)) ,
	&Reset_Handler , 
	&NMI_Handler , 
	&MM_Fault_Handler , 
	&Bus_Fault_Handler , 
};
 
