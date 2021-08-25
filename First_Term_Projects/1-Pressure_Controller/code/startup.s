/*
Startup for Cortex-M3
Author : Mahmoud Magdy Ayoub
*/

.section .vectors
.word 0x20001000        /* Stack_top     */
.word _reset 			/* 1 Reset  	 */
.word Vector_handler    /* 2 NMI  		 */
.word Vector_handler    /* 3 Hard Fault  */
.word Vector_handler    /* 4 MM Fault  	 */
.word Vector_handler    /* 5 Bus Fault   */

.section .text
_reset : 
	bl main
	b . 

.thumb_func

Vector_handler : 
	b _reset