/*
 * main.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"

// effective data
struct SData {
	char name [40] ;
	int ID ;
	float height ;
};

// Linked List Node
struct SStudent {
	struct SData Data ;
	struct SStudent* pNextStudent ;
};

// APIs
void AddStudent (void) ;
int DeleteStudent (void) ;
void ViewStudents (void) ;
void DeleteAll (void) ;
void get_Nth_node_from_head (void) ;
void get_length_of_linkedlist (void) ;
void get_Nth_node_from_end (void) ;
void reverse_linkedlist (struct SStudent** head_ref) ;
// pointer to first student
struct SStudent* ghead = NULL ;

int main () {
	int choice ;
	while (1) {
		printf ("\n=========================") ;
		printf ("\n \t choose one of the following options \n") ;
		printf ("\n 1:Add Student") ;
		printf ("\n 2:Delete Student") ;
		printf ("\n 3:View All Students") ;
		printf ("\n 4:Delete All Students") ;
		printf ("\n 5:Get Nth Student from Beginning") ;
		printf ("\n 6:Get Number of Students in DataBase") ;
		printf ("\n 7:Get Nth Student from End") ;
		printf ("\n 8:Reverse Students") ;
		printf ("\n Enter Option Number : ") ;
		fflush (stdin) ; 	fflush (stdout) ;
		scanf ("%d" , &choice) ;
		printf ("\n=========================") ;
		switch (choice) {
		case 1 :
			AddStudent() ;
			break ;
		case 2 :
			DeleteStudent() ;
			break ;
		case 3 :
			ViewStudents() ;
			break ;
		case 4 :
			DeleteAll() ;
			break ;
		case 5 :
			get_Nth_node_from_head() ;
			break;
		case 6 :
			get_length_of_linkedlist() ;
			break ;
		case 7 :
			get_Nth_node_from_end() ;
			break ;
		case 8 :
			reverse_linkedlist(&ghead) ;
			break ;
		default :
			printf ("\nWrong Option") ;
			break ;
		}
	}

	return 0 ;
}

void AddStudent (void) {
	// create new Student Node
	struct SStudent* pNewStudent = (struct SStudent*) malloc (sizeof (struct SStudent)) ;

	// check if database (linked list) is empty or not
	if (ghead == NULL) {        /* Empty List */
		// make head points to the new student node
		ghead = pNewStudent ;
	}
	else {						/* List has Records */
		// search for last element in linked list
		struct SStudent* temp = ghead ;
		while (temp->pNextStudent) {
			temp = temp -> pNextStudent ;
		}
		temp -> pNextStudent = pNewStudent ;
	}
	// fill new Student Data
	printf ("\nEnter Student Full Name : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	gets (pNewStudent->Data.name) ;

	printf ("\nEnter Student ID : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &pNewStudent->Data.ID) ;

	printf ("\nEnter Student Height : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%f" , &pNewStudent->Data.height) ;
	pNewStudent -> pNextStudent = NULL ;
}
int DeleteStudent (void) {
	int deleted_ID ;
	printf ("\nEnter the Deleted Student ID : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &deleted_ID) ;
	// check list is Not Empty
	if (ghead != NULL) {         /* Not Empty list */
		struct SStudent* pSelectedStudent = ghead ;
		struct SStudent* pPrevStudent = NULL;

		// compare each node with the selected ID
		while (pSelectedStudent) {
			if (pSelectedStudent->Data.ID == deleted_ID) {
				if (pPrevStudent) {         /* delete a middle node */
					pPrevStudent->pNextStudent = pSelectedStudent->pNextStudent ;
				}
				else {                      /* delete first node */
					ghead = pSelectedStudent->pNextStudent ;
				}
				free (pSelectedStudent)  ;
				return 1 ;
			}
			pPrevStudent = pSelectedStudent ;
			pSelectedStudent = pSelectedStudent->pNextStudent ;
		}

	}
	// Exits the loop without finding the deleted ID
	printf ("\nNo Matched ID ") ;
	return 0 ;
}
void ViewStudents (void) {
	struct SStudent* disp = ghead ;
	int count = 0 ;
	if (disp != NULL) {    /* Not Empty list */
		while (disp) {
			printf ("\nRecord Number %d " , count+1) ;
			printf ("\n \tStudent name : %s " , disp->Data.name) ;
			printf ("\n \tStudent ID : %d " , disp->Data.ID) ;
			printf ("\n \tStudent height : %f " , disp->Data.height) ;
			fflush (stdin) ; 	fflush (stdout) ;
			disp = disp->pNextStudent ;
			count ++ ;
		}

	}
	else {      /* Empty list */
		printf ("\nEmpty list") ;
	}
}
void DeleteAll (void) {
	struct SStudent* pCurrentStudent = ghead ;
	if (pCurrentStudent != NULL) {    /* Not Empty list */
		while (pCurrentStudent) {
			struct SStudent* ptemp = pCurrentStudent ;
			pCurrentStudent = pCurrentStudent->pNextStudent ;
			free (ptemp) ;
		}
		ghead = NULL ;
	}
	else {      /* Empty list */
		printf ("\nEmpty list") ;
	}
}
void get_Nth_node_from_head (void) {
	struct SStudent* temp = ghead ;
	int count = 0 ;
	int index ;
	printf ("\nEnter index required : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &index ) ;
	if (temp != NULL) {			/* Not Empty list */
		while (temp) {
			if (count == index) {
				printf ("\nIndex Number %d " , count) ;
				printf ("\n \tStudent name : %s " , temp->Data.name) ;
				printf ("\n \tStudent ID : %d " , temp->Data.ID) ;
				printf ("\n \tStudent height : %f " , temp->Data.height) ;
				fflush (stdin) ; 	fflush (stdout) ;
				break ;
			}
			temp = temp->pNextStudent ;
			count ++ ;
		}
	}
}
void get_length_of_linkedlist (void)  {
	struct SStudent* temp = ghead ;
	int count = 0 ;
	while (temp) {
		count ++ ;
		temp = temp->pNextStudent ;
	}
	printf ("\nNo of Nodes = %d " , count) ;
}
void get_Nth_node_from_end (void) {
	struct SStudent* p_ref = ghead ;
	struct SStudent* p_main = ghead ;
	int index , i ;
	printf ("\nEnter index required : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	scanf ("%d" , &index ) ;
	for (i=0 ; i<index ; i++) {
		p_ref = p_ref->pNextStudent ;
	}
	while (p_ref) {
		p_ref = p_ref -> pNextStudent ;
		p_main = p_main -> pNextStudent ;
	}
	printf ("\n======Data in element %d from end=====" , index) ;
	printf ("\n \tStudent name : %s " , p_main->Data.name) ;
	printf ("\n \tStudent ID : %d " , p_main->Data.ID) ;
	printf ("\n \tStudent height : %f " , p_main->Data.height) ;
	fflush (stdin) ; 	fflush (stdout) ;
}
void reverse_linkedlist (struct SStudent** head_ref) {
	struct SStudent* prev = NULL;
	struct SStudent* current = *head_ref;
	struct SStudent* next = NULL;
	while (current != NULL) {
		// store next node
		next = current->pNextStudent;

		// Reverse current node's pointer
		current->pNextStudent = prev;

		// Move pointers one position ahead.
		prev = current;
		current = next;
	}
	*head_ref = prev;
}

