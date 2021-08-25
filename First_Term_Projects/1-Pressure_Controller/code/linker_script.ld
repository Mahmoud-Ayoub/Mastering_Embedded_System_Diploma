MEMORY
{
	flash(RX) : ORIGIN = 0x08000000 , LENGTH = 128k 
	SRAM(RWX) : ORIGIN = 0x20000000 , LENGTH = 20k 
}

SECTIONS 
{
	.text : {
		*(.vectors*)
		*(.text*)
	} > flash

	.data : {
		*(.data)
	} > SRAM AT> flash

	.bss : {
		*(.bss)
	} > SRAM
}
