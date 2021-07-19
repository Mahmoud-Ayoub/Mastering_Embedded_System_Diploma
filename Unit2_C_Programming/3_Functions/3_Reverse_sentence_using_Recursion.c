/*
 * 3_Reverse_sentence_using_Recursion.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
#include "string.h"
void reverse_string (char str [] , int begin ,int end) ;

int main () {
	char sentence [50] ;
	printf ("Enter a sentence : ") ;
	fflush (stdin) ; 	fflush (stdout) ;
	gets (sentence) ;
	reverse_string (sentence , 0 ,strlen(sentence)-1) ;
	printf ("%s " , sentence) ;
	return 0 ;
}
void reverse_string (char str [] , int begin ,int end) {
	char c ;
	if (begin >= end)
		return ;
	c = str[begin] ;
	str[begin] = str[end] ;
	str[end] = c ;
	reverse_string (str , ++begin , --end) ;
}

