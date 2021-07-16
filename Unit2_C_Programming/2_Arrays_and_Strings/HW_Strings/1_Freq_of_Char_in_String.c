/*
 * 1_Freq_of_Char_in_String.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
int main () {
	char str [40] ;
	char c_check ;
	int i = 0 ;
	int freq = 0 ;

	printf ("Enter a string : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	gets (str) ;
	printf ("Enter a character to find frequency : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%c" , &c_check) ;
	while (str[i] != 0) {
		if (str[i] == c_check)
			freq++ ;
		i++ ;
	}
	printf ("Frequency of %c = %d " , c_check , freq) ;
	return 0 ;
}


