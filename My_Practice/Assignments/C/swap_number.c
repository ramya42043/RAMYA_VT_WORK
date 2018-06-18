#include<stdio.h>
int main()
{
int a,b;
printf("enter two numbwrs:");
scanf("%d %d",&a,&b);
a = a^b;
b = a^b;
a = a^b;
printf("after swapping a = %d b= %d\n",a,b);
}
