/*
 * 2_Add_Two_Ditances_using_Struct.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
struct SDistance {
	int feet ;
	float inch ;
};
int main () {
	struct SDistance d1 , d2 , sum ;
	printf ("Enter Information for 1st distance : \n") ;
	printf ("Enter feet : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &d1.feet) ;
	printf ("Enter inch : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%f" , &d1.inch) ;

	printf ("\nEnter Information for 2nd distance : \n") ;
	printf ("Enter feet : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &d2.feet) ;
	printf ("Enter inch : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%f" , &d2.inch) ;

	sum.feet = d1.feet + d2.feet ;
	sum.inch = d1.inch + d2.inch ;

	if (sum.inch > 12.0) {
		sum.inch -= 12.0 ;
		sum.feet ++ ;
	}
	printf ("\nSum of distances = %d\'-%.1f\"" , sum.feet , sum.inch) ;
	return 0 ;
}

