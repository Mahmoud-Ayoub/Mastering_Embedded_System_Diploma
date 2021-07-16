/*
 * 2_Average_using_Arrays.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
int main () {
	float numbers [10] ;
	int n , i ;
	float sum = 0 , average = 0 ;
	printf ("Enter number of data between 0 to 10 \n") ;
	printf ("Enter the number of data : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &n) ;
	if (n<=0 || n>10) {
		printf ("Error !!") ;
	}
	else {
		for (i=0 ; i<n ; i++) {
			printf ("Enter number : ") ;
			fflush (stdin) ; 	fflush (stdout) ;
			scanf ("%f" , &numbers[i]) ;
			sum += numbers[i] ;
		}
		average = sum / n ;
		printf("Average = %.2f " , average) ;
	}
	return 0 ;
}



