/*
 * 2_Length_of_String_without_strlen.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
int main () {
	char str[15] ;
	int i = 0 ;

	printf ("Enter a string : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%s" , str) ;
	while (str[i] != 0) {
		i ++ ;
	}
	printf ("Length of string : %d " , i) ;


	return 0 ;
}


