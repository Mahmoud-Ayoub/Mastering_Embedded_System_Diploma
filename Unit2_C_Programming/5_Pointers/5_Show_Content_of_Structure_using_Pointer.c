/*
 * 5_Show_Content_of_Structure_using_Pointer.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
struct SEmployee {
	char name [20] ;
	int ID ;
};
int main () {
	struct SEmployee e1 = {"Alex" , 1002} ;
	struct SEmployee* p_e1 = &e1 ;
	struct SEmployee e2 = {"Mahmoud" , 2002} ;
	struct SEmployee* p_e2 = &e2 ;
	struct SEmployee* arr_emp[] = {p_e1 , p_e2} ;    // array of pointers to structures

	printf ("Employee Name : %s \n" , arr_emp[0]->name ) ;
	printf ("Employee ID : %d \n" , arr_emp[0]->ID) ;
	return 0 ;
}


