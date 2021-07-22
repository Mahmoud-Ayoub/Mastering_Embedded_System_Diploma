/*
 * 5_Area_of_Circle_using_Macros.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
#define AREA_OF_CIRCLE(r) (3.14*(r)*(r))
int main () {
	float radius ;
	float area = 0 ;
	printf ("Enter the radius : ") ;
	fflush (stdin) ; 	fflush(stdout) ;
	scanf ("%f" , &radius) ;
	area = AREA_OF_CIRCLE(radius) ;
	printf ("Area = %.2f " , area) ;

	return 0 ;
}


