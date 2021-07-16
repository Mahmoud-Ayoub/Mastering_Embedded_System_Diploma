/*
 * main.c
 *
 *      Author: Mahmoud Ayoub
 */

#include "stdio.h"

int main () {

	int i = 0 ;
	int j= 0 ;

	for (i=0 ; i<=9 ; i++)  {
		for (j=i ; j<=9 ; j++) {
			printf ("%d " , j) ;
		}
		printf("\n") ;
	}

	return 0 ;
}
