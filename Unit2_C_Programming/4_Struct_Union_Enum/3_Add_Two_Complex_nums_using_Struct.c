/*
 * 3_Add_Two_Complex_nums_using_Struct.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
struct SComplex_num {
	float real ;
	float img ;
};
struct SComplex_num Add (struct SComplex_num a ,struct SComplex_num b) {
	struct SComplex_num s = {0 , 0} ;
	s.real = a.real + b.real ;
	s.img = a.img + b.img ;
	return s ;
}
int main () {
	struct SComplex_num n1 , n2 , sum ;
	printf ("For 1st complex number \n") ;
	printf ("Enter real and imaginary respectively : ") ;
	fflush (stdin) ;	fflush (stdout) ;
	scanf ("%f %f" , &n1.real , &n1.img) ;

	printf ("For 2nd complex number \n") ;
	printf ("Enter real and imaginary respectively : ") ;
	fflush (stdin) ;	fflush (stdout) ;
	scanf ("%f %f" , &n2.real , &n2.img) ;

	sum = Add(n1 , n2) ;
	printf ("Sum = %.1f + %.1fi " , sum.real , sum.img) ;
	return 0 ;
}


