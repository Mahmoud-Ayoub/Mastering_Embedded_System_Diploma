/*
 * system.c
 *      Author: Mahmoud Ayoub
 */
#include "system.h"
int students_count = 0 ;

int is_Full (void) {
	if (students_count == MAX) {
		return 1 ;
	}
	else
		return 0 ;
}
int is_Empty (void) {
	if (students_count == 0) {
		return 1 ;
	}
	else
		return 0 ;
}
void Print_Students_info (void) {
	int i = 0 ;
	int j = 0 ;
	if (is_Empty() == 1) {
		printf ("[Error] Buffer is Empty \n") ;
	}
	else {
		for (i=0 ; i<students_count ; i++) {
			fflush (stdin) ; 	fflush (stdout) ;
			printf ("\n-------------Student %d info--------------- \n" , i+1) ;
			printf ("First name : %s \n" , Students_buffer[i].first_name) ;
			printf ("Last name  : %s \n" , Students_buffer[i].last_name) ;
			printf ("ID  : %d \n" , Students_buffer[i].ID) ;
			printf ("GPA : %.2f \n" , Students_buffer[i].GPA) ;
			printf ("Registered Courses : ") ;
			for (j=0 ; j<4 ; j++) {
				printf ("%d " , Students_buffer[i].courses_ID[j] ) ;
			}
		}
	}
}
void Add_Student_Manually (void) {
	int i = 0 ;
	if (is_Full() == 1) {
		printf ("[Error] Buffer is Full \n") ;
	}
	else {
		printf ("Enter Student First Name : ") ;            // get first name
		fflush (stdin) ; 	fflush (stdout) ;
		gets (Students_buffer[students_count].first_name) ;

		printf ("Enter Student Last Name : ") ;			    // get last name
		fflush (stdin) ; 	fflush (stdout) ;
		gets (Students_buffer[students_count].last_name) ;

		printf ("Enter Student ID : ") ; 					// get ID
		fflush (stdin) ; 	fflush (stdout) ;
		scanf ("%d" , &Students_buffer[students_count].ID) ;

		printf ("Enter Student GPA : ") ; 					// get GPA
		fflush (stdin) ; 	fflush (stdout) ;
		scanf ("%f" , &Students_buffer[students_count].GPA) ;

		printf ("Enter Student Courses ID : ") ;
		fflush (stdin) ; 	fflush (stdout) ;
		for (i=0 ; i<4 ; i++) {
			scanf ("%d" , &Students_buffer[students_count].courses_ID[i]);
		}
		students_count ++ ;         // increment number of students in buffer
		printf ("Students Count = %d \n" , students_count) ;
	}
}

void Add_Student_From_File (void) {
	int i = 0 ;
	int j = 0 ;
	int k = 0 ;
	int no_of_lines = 2 ;
	float GPA_float ;
	char read_data [100] ;
	char* tokens_arr[10] ;        // 2-D array to store every line in the info file
	char* token ;
	int int_tokens [10] ;            // array of integers to store int values in data
	char* pend ;
	FILE* f_ptr ;

	f_ptr = fopen ("info.txt" , "r") ;         // read from the info file
	if (f_ptr == NULL) {
		printf ("[Error]  Couldn't open file \n") ;
	}
	else {
		printf ("File Opened Successfully \n") ;
		for (k=0 ; k<no_of_lines ; k++) {
			i = 0 ;
			j = 0 ;
			fgets(read_data , 100 , f_ptr) ;
			fflush (stdin) ; 	fflush (stdout) ;
			puts (read_data) ;

			// parse line
			token = strtok(read_data , DELIM) ;
			while (token != NULL) {
				tokens_arr[j] = token ;
				j++ ;
				token = strtok (NULL , DELIM) ;
			}
			tokens_arr [j] = NULL ;

			for (i=0 ; i<8 ; i++) {
				printf ("string token = %s \n" , tokens_arr[i]) ;
			}
			for (i=2 ; i<8 ; i++) {
				if (i==3) {
					// GPA is a float
					GPA_float = strtof(tokens_arr[3] , &pend)  ;
					continue ;
				}
				int_tokens[i] = atoi(tokens_arr[i]);
			}
			// store data in database after parsing
			strcpy(Students_buffer[students_count].first_name , tokens_arr[0]) ;
			strcpy(Students_buffer[students_count].last_name , tokens_arr[1]) ;
			Students_buffer[students_count].ID = int_tokens[2] ;
			Students_buffer[students_count].GPA = GPA_float ;
			Students_buffer[students_count].courses_ID[0] = int_tokens[4] ;
			Students_buffer[students_count].courses_ID[1] = int_tokens[5] ;
			Students_buffer[students_count].courses_ID[2] = int_tokens[6] ;
			Students_buffer[students_count].courses_ID[3] = int_tokens[7] ;
			students_count ++ ;
		}
	}
}
void Find_with_ID (void) {
	int i = 0 ;
	int j = 0 ;
	int searched_ID ;
	printf ("Enter Searched ID : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &searched_ID) ;

	for (i=0 ; i<students_count ; i++) {
		if (Students_buffer[i].ID == searched_ID) {
			break ;
		}
	}
	if (i == students_count) {
		printf ("[Error] ID NOT Found \n") ;
	}
	else {						// ID is Found
		printf ("First name : %s \n" , Students_buffer[i].first_name) ;
		printf ("Last name  : %s \n" , Students_buffer[i].last_name) ;
		printf ("ID  : %d \n" , Students_buffer[i].ID) ;
		printf ("GPA : %.2f \n" , Students_buffer[i].GPA) ;
		printf ("Registered Courses : ") ;
		for (j=0 ; j<4 ; j++) {
			printf ("%d " , Students_buffer[i].courses_ID[j] ) ;
		}
		printf ("\n") ;
	}
}

void Find_with_First_name (void) {
	int i = 0 ;
	int j = 0 ;
	char searched_name [20] ;
	printf ("Enter Searched First Name : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	gets (searched_name) ;
	for (i=0 ; i<students_count ; i++) {
		if (stricmp(Students_buffer[i].first_name , searched_name) == 0) {
			break ;
		}
	}
	if (i == students_count) {
		printf ("[Error] First Name NOT Found \n") ;
	}
	else {
		printf ("First name : %s \n" , Students_buffer[i].first_name) ;
		printf ("Last name  : %s \n" , Students_buffer[i].last_name) ;
		printf ("ID  : %d \n" , Students_buffer[i].ID) ;
		printf ("GPA : %.2f \n" , Students_buffer[i].GPA) ;
		printf ("Registered Courses : ") ;
		for (j=0 ; j<4 ; j++) {
			printf ("%d " , Students_buffer[i].courses_ID[j] ) ;
		}
		printf ("\n") ;
	}
}
void Find_Students_in_course (void) {
	int i = 0 ;
	int j = 0 ;
	int searched_course ;
	int flag = 0 ;
	printf ("Enter Searched Course : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &searched_course) ;
	for (i=0 ; i<students_count ; i++) {
		for (j=0 ; j<4 ; j++) {
			if (Students_buffer[i].courses_ID[j] == searched_course) {
				flag = 1 ;
				printf ("Student number %d registered course %d \n" , i+1 , searched_course) ;
			}
		}
	}
	if ( (i == students_count) && (flag == 0)) {
		printf ("[Error] Course ID NOT Found \n") ;
	}
}
void Find_Students_Count (void) {
	printf ("Count of Students = %d \n" , students_count) ;
}
void Delete_Student_with_ID (void) {
	int i = 0 ;
	int j = 0 ;
	int deleted_ID ;
	int flag = 0 ;

	printf ("Enter Deleted ID : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &deleted_ID) ;

	for (i=0 ; i<students_count ; i++) {
		if (Students_buffer[i].ID == deleted_ID) {
			flag = 1 ;
			students_count -- ;
			// delete this student from array
			for (j=i ; j<students_count ; j++) {
				Students_buffer[j] = Students_buffer[j+1] ;
			}
		}
	}
	if ( (i == students_count) && (flag == 0) ) {
		printf ("[Error] ID NOT Found \n") ;
	}
}

void Update_Student_with_ID (void) {
	int i = 0 ;
	int j = 0 ;
	int updated_ID ;
	int update_choice ;

	printf ("Enter Updated ID : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &updated_ID) ;
	for (i=0 ; i<students_count ; i++) {
		if (Students_buffer[i].ID == updated_ID) {
			break ;
		}
	}
	if (i == students_count) {
		printf ("[Error] ID NOT Found \n") ;
	}
	else {             // ID is Found
		printf ("1 : Update First Name \n") ;
		printf ("2 : Update Last Name \n") ;
		printf ("3 : Update ID \n") ;
		printf ("4 : Update GPA \n") ;
		printf ("5 : Update Courses ID \n") ;
		printf ("enter update choice : ") ;
		fflush (stdin) ; 	fflush (stdout) ;
		scanf ("%d", &update_choice) ;

		switch (update_choice) {
		case 1 :
			printf ("Enter New First Name : ") ;
			fflush (stdin) ; 	fflush (stdout) ;
			gets (Students_buffer[i].first_name) ;
			break ;

		case 2 :
			printf ("Enter New Last Name : ") ;
			fflush (stdin) ; 	fflush (stdout) ;
			gets (Students_buffer[i].last_name) ;
			break ;

		case 3 :
			printf ("Enter New ID : ") ;
			fflush (stdin) ; 	fflush (stdout) ;
			scanf ("%d" , &Students_buffer[i].ID) ;
			break ;

		case 4 :
			printf ("Enter New GPA : ") ;
			fflush (stdin) ; 	fflush (stdout) ;
			scanf ("%f" , &Students_buffer[i].GPA) ;
			break ;

		case 5 :
			printf ("Enter Student Courses ID : ") ;
			fflush (stdin) ; 	fflush (stdout) ;
			for (j=0 ; j<4 ; j++) {
				scanf ("%d" , &Students_buffer[i].courses_ID[j]);
			}
			break ;

		default :
			printf ("[Error] Wrong Choice \n") ;
			break ;
		}
	}
}
