/*
 * 4_Store_Info_of_10_Students_using_Struct.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
struct SStudent {
	char name [20] ;
	int roll ;
	int marks ;
};
int main () {
	struct SStudent students[10] ;
	int i = 0 ;
	printf ("Enter information of students : \n") ;
	for (i=0 ; i<10 ; i++) {
		printf ("\nFor roll number %d \n" , i+1) ;
		printf ("Enter name : ") ;
		fflush (stdin) ; 	fflush (stdout) ;
		scanf ("%s" , students[i].name) ;
		printf ("Enter marks : ") ;
		fflush (stdin) ; 	fflush (stdout) ;
		scanf ("%d" , &students[i].marks) ;
	}

	printf ("\nDisplaying information of students : \n") ;
	for (i=0 ; i<10 ; i++) {
		printf ("\nInformation For roll number %d \n" , i+1) ;
		printf ("Name : %s \n" , students[i].name) ;
		printf ("Marks : %d \n " , students[i].marks) ;
	}

	return 0 ;
}


