/*
 * 2_Print_Alphabets_using_Pointer.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"

int main () {
	char c = 'A' ;
	char* p_c = &c ;
	unsigned int i = 0 ;
	for (i=0 ; i<26 ; i++) {
		printf ("%c \n" , *p_c) ;
		c++ ;
	}
	return 0 ;
}
