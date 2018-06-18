#include<stdio.h>
int main()
{
int a=0,b=1,c,n;
printf("enter a number:");
scanf("%d",&n);
//printf("%d %d ",a,b);
for(int i=0;i<n;i++)
{
c = a+b;
b=c;
a=b;
printf("%d ",c);
}
printf("\n");
}
