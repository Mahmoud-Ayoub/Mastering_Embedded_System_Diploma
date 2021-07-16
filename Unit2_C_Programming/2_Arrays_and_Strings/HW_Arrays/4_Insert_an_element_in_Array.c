/*
 * 4_Insert_an_element_in_Array.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
int main () {
	int arr [10] ;
	int n , i ;
	int inserted_element , inserted_pos ;
	printf ("Enter no of elements : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &n) ;
	for (i=0 ; i<n ; i++) {
		printf ("Enter an element : ") ;
		fflush (stdin) ; 	fflush (stdout) ;
		scanf ("%d" , &arr[i]) ;
	}
	printf ("Enter the element to be inserted : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &inserted_element) ;

	printf ("Enter the location : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &inserted_pos) ;

	n++ ;
	for (i=n-1 ; i>=inserted_pos ; i--) {
		arr[i] = arr[i-1] ;
	}
	arr[inserted_pos-1] = inserted_element ;
	for (i=0 ; i<n ; i++) {
		printf ("%d \t" , arr[i]) ;
	}
	return 0 ;
}

