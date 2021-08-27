/*
 * system.h
 *      Author: Mahmoud Ayoub
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX 50
#define DELIM " \t\r\n\a"

struct SStudent {
	char first_name [20] ;
	char last_name [20] ;
	int ID ;
	float GPA ;
	int courses_ID [4] ;
}Students_buffer[MAX];

int is_Full (void) ;
int is_Empty (void) ;
void Print_Students_info (void) ;
void Add_Student_Manually (void) ;
void Add_Student_From_File (void) ;
void Find_with_ID (void) ;
void Find_with_First_name (void) ;
void Find_Students_in_course (void) ;
void Find_Students_Count (void) ;
void Delete_Student_with_ID (void) ;
void Update_Student_with_ID (void) ;


#endif /* SYSTEM_H_ */
