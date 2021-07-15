/*
 * EX7.c
 *
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
int main () {
	int n , i ;
	int factorial = 1 ;
	printf ("Enter a number : ") ;
	fflush (stdin);  	fflush (stdout) ;
	scanf ("%d" , &n) ;
	if (n > 0) {
		for (i=n ; i>=1 ; i--) {
			factorial *= i ;
		}
		printf ("Factorial = %d " , factorial) ;
	}
	else if (n < 0)
		printf ("Error!!! Factorial of negative number doesn't exist ") ;
	else
		printf ("Factorial = 1") ;

	return 0 ;
}


