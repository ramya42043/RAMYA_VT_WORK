#include<stdio.h>
/*Expected result is 36
But we are getting 37
By using volatile we are getting expected value */
main()
{
//volatile int a=10,b=0;
int a=10,b=0;
b = a++ + ++a + ++a ; 
printf("%d %d\n",a,b);

}
