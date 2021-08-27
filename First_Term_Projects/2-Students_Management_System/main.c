/*
 * main.c
 *      Author: Mahmoud Ayoub
 */
#include "system.h"

int main () {
	int choice ;
	int exit_flag = 0 ;
	while (exit_flag == 0) {
		printf ("\n-------------------------------------------\n") ;
		printf ("1  : Add New Student Manually \n") ;
		printf ("2  : Add New Student from File \n") ;
		printf ("3  : Find Student With ID \n") ;
		printf ("4  : Find Student With First Name \n") ;
		printf ("5  : Find Students Registered in a course \n") ;
		printf ("6  : Find Students Count \n") ;
		printf ("7  : Delete a Student \n") ;
		printf ("8  : Update a Student \n") ;
		printf ("9  : View All Students \n") ;
		printf ("10 : Exit \n") ;

		printf ("Enter a choice : ") ;
		fflush (stdin) ; 	fflush (stdout) ;
		scanf ("%d" , &choice) ;
		switch (choice) {
		case 1 :
			Add_Student_Manually () ;
			break ;

		case 2 :
			Add_Student_From_File () ;
			break ;

		case 3 :
			Find_with_ID() ;
			break ;

		case 4 :
			Find_with_First_name() ;
			break ;

		case 5 :
			Find_Students_in_course() ;
			break ;

		case 6 :
			Find_Students_Count() ;
			break ;

		case 7 :
			Delete_Student_with_ID() ;
			break ;

		case 8 :
			Update_Student_with_ID() ;
			break ;

		case 9 :
			Print_Students_info() ;
			break ;

		case 10 :
			exit_flag = 1 ;
			printf ("System is Exited \n") ;
			break ;

		default :
			printf ("[Error] Wrong Choice \n") ;
			break ;
		}
	}
	return 0 ;
}
