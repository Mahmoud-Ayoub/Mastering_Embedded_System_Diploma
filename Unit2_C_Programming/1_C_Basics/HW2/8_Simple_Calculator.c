 /* EX8.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
int main () {
	char op ;
	float n1 , n2 ;
	printf ("Enter operator either + or - or * or / : ") ;
	fflush (stdin);  	fflush (stdout) ;
	scanf ("%c" , &op);
	printf ("Enter two operands : ") ;
	fflush (stdin);  	fflush (stdout) ;
	scanf ("%f %f" , &n1 , &n2) ;
	switch (op) {
	case '+' :
		printf ("%.1f + %.1f = %.1f" , n1 , n2 , n1+n2) ;
		break ;
	case '-' :
		printf ("%.1f - %.1f = %.1f" , n1 , n2 , n1-n2) ;
		break ;
	case '*' :
		printf ("%.1f * %.1f = %.1f" , n1 , n2 , n1*n2) ;
		break ;
	case '/' :
		if (n2 == 0)
			printf ("Runtime Error !!! Divide by zero") ;
		else
			printf ("%.1f / %.1f = %.1f" , n1 , n2 , n1/n2) ;
		break ;
	default :
		printf ("Error !!! operator is not correct") ;
	}
	return 0 ;
}

