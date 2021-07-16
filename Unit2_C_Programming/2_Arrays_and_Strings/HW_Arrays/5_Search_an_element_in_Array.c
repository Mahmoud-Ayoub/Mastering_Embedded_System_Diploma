/*
 * 5_Search_an_element_in_Array.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
int main () {
	int arr [10] ;
	int n , i ;
	int searched_element ;
	printf ("Enter no of elements : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &n) ;
	for (i=0 ; i<n ; i++) {
		printf ("Enter an element : ") ;
		fflush (stdin) ; 	fflush (stdout) ;
		scanf ("%d" , &arr[i]) ;
	}
	printf ("Enter the element to be searched : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &searched_element) ;

	for (i=0 ; i<n ; i++) {
		if (arr[i]==searched_element)
			break ;
	}
	if (i<n) {
		printf ("Number found at the location : %d " , i+1) ;
	}
	else {
		printf ("Number NOT found ") ;
	}

	return 0 ;
}

