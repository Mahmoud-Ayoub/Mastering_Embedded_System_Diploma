/*
 * 3_Reverse_String_using_Pointer.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
#include "string.h"
int main () {
	char str[20] ;
	char str_reversed [20] ;
	char* p_str = str ;
	char* p_str_reversed = str_reversed ;
	int i = -1 ;
	printf ("Input a string : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	gets (str) ;
	while (*p_str) {
		p_str ++ ;
		i ++ ;
	}
	while (i >= 0) {
		p_str -- ;
		*p_str_reversed = *p_str ;
		p_str_reversed ++ ;
		i -- ;
	}
	*p_str_reversed = 0 ;
	printf ("\n%s" , str_reversed) ;
	return 0 ;
}

