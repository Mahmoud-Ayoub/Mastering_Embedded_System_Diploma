/*
 * Prime_Numbers_between_intervals.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
void prime_numbers (int min , int max) ;
int check_prime (int num) ;

int main () {
	int n1 , n2 ;
	printf("Enter two numbers (intervals) : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d %d" , &n1 , &n2) ;
	prime_numbers(n1,n2) ;

	return 0 ;
}
void prime_numbers (int min , int max) {
	int i = 0 ;
	int flag = 0;
	printf ("Prime numbers between %d and %d are : " , min , max ) ;
	for (i=min ; i<=max ; i++) {
		flag = check_prime(i) ;
		if (flag == 1)
			printf ("%d \t" , i) ;
	}
}
int check_prime (int num) {
	int c;
	for (c = 2; c <= num-1; c++)
	{
		if (num%c == 0)
			return 0;
	}
	if (c == num)
		return 1;
}
