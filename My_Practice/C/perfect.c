#include<stdio.h>
int main()
{
int num,sum=0;
printf("enter number:");
scanf("%d",&num);
for(int i=1;i<=num/2;i++)
{
	if((num%i)==0)
	{
		sum += i;
	}
}
if(num==sum)
printf("%d is perfect number\n",num);
else
printf("Not perfect number\n");
}
