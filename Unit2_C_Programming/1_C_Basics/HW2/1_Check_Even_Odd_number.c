/*
 * EX1.c
 *
 *      Author: Mahmoud Ayoub
 */

#include "stdio.h"

int main () {
	int num ;
	printf ("Enter an integer you want to check : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &num);
	if (num % 2 == 0)
		printf ("%d is even number " , num) ;
	else
		printf ("%d is odd number " , num) ;


	return 0 ;
}

