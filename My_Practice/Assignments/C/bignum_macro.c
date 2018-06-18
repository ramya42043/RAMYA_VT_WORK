#include<stdio.h>
#define big(a,b,c) (a>b?(a>c?a:c):(b>c?b:c))
int main()
{
int res = big(10,2,3);
printf("big number is %d\n",res);
}
