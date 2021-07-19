/*
 * 2_Factorial_using_Recursion.c
 *      Author: Mahmoud Ayoub
 */

#include "stdio.h"

int factorial (int n) ;

int main () {
	int num ;
	int result ;
	printf ("Enter a positive integer : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &num) ;
	result = factorial (num) ;
	printf ("Factorial of %d = %d " , num , result) ;
	return 0 ;
}
int factorial (int n) {
	if (n > 1)
		return n*factorial(n-1) ;
}

