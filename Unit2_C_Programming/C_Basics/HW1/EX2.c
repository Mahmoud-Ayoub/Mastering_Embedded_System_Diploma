/*
 * EX2.c
 *
 *      Author: Mahmoud Ayoub
 */

#include "stdio.h"

int main () {
	int num ;
	printf("Enter an Integer : ") ;
	fflush (stdin) ; fflush (stdout) ;
	scanf ("%d" , &num) ;
	printf ("You entered : %d" , num) ;

	return 0 ;
}

