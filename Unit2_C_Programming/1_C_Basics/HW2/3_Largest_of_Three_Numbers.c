/*
 * EX3.c
 *
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"

int main () {
	float n1 , n2 , n3 ;
	printf ("Enter three numbers : ") ;
	fflush (stdin);  	fflush (stdout) ;
	scanf ("%f %f %f" , &n1 , &n2 , &n3) ;
	if (n1 > n2) {
		if (n1 > n3)
			printf ("Largest number = %.2f " , n1) ;
		else
			printf ("Largest number = %.2f " , n3) ;
	}
	else if (n2 > n1) {
		if (n2 > n3)
			printf ("Largest number = %.2f " , n2) ;
		else
			printf ("Largest number = %.2f " , n3) ;
	}
	return 0 ;
}

