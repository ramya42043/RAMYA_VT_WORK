#include<stdio.h>
int fun(int n)
{
while(n!=1)
{
if(n%2!=0)
  return 0;
n=n/2;
}
return 1;
}
int main()
{
int num;
printf("enter a number");
scanf("%d",&num);
int res = fun(num);
if(res)
printf("power of 2\n");
else
printf("not power of 2\n");
}

