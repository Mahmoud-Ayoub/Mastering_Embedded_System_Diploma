/*
 * EX7.c
 *
 *      Author: Mahmoud Ayoub
 */

#include "stdio.h"

int main () {
	int a , b ;
	printf ("Enter value of a : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &a) ;
	printf ("Enter value of b : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &b) ;
	a = a + b ;
	b = a - b ;
	a = a - b ;

	printf ("After swapping, value of a = %d \n" , a) ;
	printf ("After swapping, value of b = %d " , b) ;

	return 0 ;
}

