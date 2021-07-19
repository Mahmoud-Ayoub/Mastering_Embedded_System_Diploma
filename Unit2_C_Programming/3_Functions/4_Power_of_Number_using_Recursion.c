/*
 * 4_Power_of_Number_using_Recursion.c
 *      Author: Blu-Ray
 */
#include "stdio.h"
int power (int base , int p) ;

int main () {
	int num , pow , result ;
	printf ("Enter base number : ") ;
	fflush (stdin) ;	fflush (stdout) ;
	scanf ("%d" , &num) ;
	printf ("Enter power number (positive integer) : ") ;
	fflush (stdin) ;	fflush (stdout) ;
	scanf ("%d" , &pow) ;
	result = power (num , pow) ;
	printf ("%d ^ %d = %d" , num , pow , result) ;
	return 0 ;
}
int power (int base , int p) {
	if (p != 0)
		return base*power(base,p-1);
	else
		return 1 ;
}


