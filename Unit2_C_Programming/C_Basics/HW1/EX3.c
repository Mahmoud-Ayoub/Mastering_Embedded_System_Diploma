/*
 * EX3.c
 *
 *      Author: Mahmoud Ayoub
 */

#include <stdio.h>
int main( )
{
    int n1, n2, sum;
    printf("Enter two integers: ");
    fflush (stdin) ;  fflush (stdout) ;
    scanf("%d %d",&n1,&n2);
    sum=n1+n2;
    printf("Sum: %d",sum);
    return 0;
}
