/*
 * 4_Reverse_elements_using_Pointers.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
int main () {
	int arr[15] ;
	int* p_arr = arr ;
	int n , i ;
	printf ("Input the number of elements to store in the array (max 15) : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" ,&n) ;

	printf ("Input %d number of elements in the array :\n" , n) ;
	fflush (stdin) ; 	fflush (stdout) ;
	for (i=0 ; i<n ; i++) {
		printf ("element -%d : " , i+1) ;
		fflush (stdin) ; 	fflush (stdout) ;
		scanf ("%d" , &arr[i]) ;
		p_arr ++ ;
	}
	p_arr = &arr[n-1] ;
	printf ("\n The elements of array in reverse order are : \n") ;
	for (i=n ; i>0 ; i--) {
		printf ("element -%d : %d \n" , i+1 , *p_arr ) ;
		p_arr -- ;
	}
	return 0 ;
}


