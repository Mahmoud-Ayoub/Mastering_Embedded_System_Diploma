/*
 * 3_Reverse_String.c
 *      Author: Mahmoud Ayoub
 */

#include "stdio.h"
#include "string.h"

int main () {
	char str[15] ;
	char str_reversed [15] ;
	int i = 0 ;
	int n = 0 ;
	printf ("Enter the string : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%s" , str) ;
	n = strlen (str) ;
	for (i=0 ; i<n ; i++) {
		str_reversed[i] = str[n-i-1] ;
	}
	str_reversed[i] = 0 ;
	printf ("Reversed String is : %s" , str_reversed) ;
	return 0 ;
}

