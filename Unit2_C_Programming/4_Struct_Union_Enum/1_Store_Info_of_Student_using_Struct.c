/*
 * 1_Store_Info_of_Student_using_Struct.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
struct SStudent {
	char name [20] ;
	int roll ;
	float marks ;
};
int main () {
	struct SStudent student1 ;
	printf ("Enter information of students: \n") ;
	printf("Enter name : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf("%s" , student1.name) ;

	printf("Enter roll number : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf("%d" , &student1.roll) ;

	printf("Enter marks : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf("%f" , &student1.marks) ;

	printf ("\nDisplaying Information \n") ;
	printf ("Name : %s \n" , student1.name) ;
	printf ("Roll : %d \n" , student1.roll) ;
	printf ("Marks : %.2f \n" , student1.marks) ;

	return 0 ;
}

