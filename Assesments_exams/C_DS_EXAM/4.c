#include<stdio.h>
//function_pointer.c

void add(int a,int b)
{
printf("addition=%d\n",a+b);
}
void sub(int a,int b)
{
printf("subtraction=%d\n",a-b);
}
void mul(int a,int b)
{
printf("multipication=%d\n",a*b);
}
void div(int a,int b)
{
printf("division=%d\n",a/b);
}
int main()
{
int num1,num2;
printf("enter num1,num2:");
scanf("%d %d",&num1,&num2);
void (*fp)(int,int);
fp = &add;
(*fp)(num1,num2);
fp = &sub;
(*fp)(num1,num2);
fp = &mul;
(*fp)(num1,num2);
fp = &div;
(*fp)(num1,num2);
}
