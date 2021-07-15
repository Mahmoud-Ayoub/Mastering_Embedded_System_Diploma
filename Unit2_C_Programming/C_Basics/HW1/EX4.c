/*
 * EX4.c
 *
 *      Author: Mahmoud Ayoub
 */

#include "stdio.h"

int main () {
	float n1 , n2 , mul ;
	printf ("Enter 2 numbers : ") ;
	fflush (stdin) ;	fflush (stdout) ;
	scanf ("%f %f" , &n1 , &n2) ;
	mul = n1 * n2 ;
	printf ("Product = %f " , mul) ;


	return 0 ;
}


