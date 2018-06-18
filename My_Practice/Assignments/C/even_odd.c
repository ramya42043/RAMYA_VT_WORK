#include<stdio.h>
void fun(n)
{
(n&1)==0?printf("even\n"):printf("odd\n");
}
int main()
{
int num;
printf("enter a number:");
scanf("%d",&num);
fun(num);
}
