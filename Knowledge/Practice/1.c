#include<stdio.h>
int *fun()
{
int a;
int *ptr = &a;
return ptr;
}
int main()
{
int a;
int *res = fun();
if(res>&a)
{
printf("stack is growing upward\n");
}
else
printf("stack is growing downward\n");
}
