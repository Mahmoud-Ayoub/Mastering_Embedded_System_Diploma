/*
 * 3_Transpose_of_Matrix.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
int main () {
	int m[6][6] ;
	int t[6][6] ;
	int r , c ;
	int i , j ;
	printf ("Range of Rows and Columns is from 1 to 6 \n") ;
	printf ("Enter number of rows and columns of matrix : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d %d" , &r , &c ) ;
	if (r<1 || c<1 || r>6 || c>6) {
		printf ("Error !!!") ;
	}
	else {
		printf ("Enter elements of matrix : \n") ;
		for (i=0 ; i<r ; i++) {
			for (j=0 ; j<c ; j++) {
				printf ("Enter element %d%d : " , i+1 , j+1) ;
				fflush (stdin) ; 	fflush (stdout) ;
				scanf ("%d" , &m[i][j]) ;
			}
		}
		printf ("Entered matrix : \n") ;
		for (i=0 ; i<r ; i++) {
			for (j=0 ; j<c ; j++) {
				printf ("%d \t" , m[i][j]) ;
			}
			printf ("\n") ;
		}
		for (i=0 ; i<r ; i++) {
			for (j=0 ; j<c ; j++) {
				t[j][i] = m[i][j] ;
			}
		}
		printf("Transpose of matrix : \n") ;
		for (i=0 ; i<c ; i++) {
			for (j=0 ; j<r ; j++) {
				printf ("%d \t" , t[i][j]) ;
				if (j==r-1)
					printf ("\n") ;
			}
		}
	}
	return 0 ;
}


