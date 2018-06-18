#include<stdio.h>
/*int fun(int *ptr)
{
*ptr =10;
printf("in function :%d\n",*ptr);
return *ptr;
}*/
int fun(int ptr)
{
ptr =10;
printf("in function :%d\n",ptr);
return ptr;
}

int main()
{
int a,res;
printf("enter a number:");
scanf("%d",&a);
//res = fun(&a);
res = fun(a);
printf("res :%d  a:%d\n",res,a);
return 0;
}

