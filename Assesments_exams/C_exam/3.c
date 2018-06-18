#include<stdio.h>
int main()
{
int num,a=0,b=1,c=0,flag =0;
printf("enter a number:");
scanf("%d",&num);
while(c<num)
{
	c=a+b;
	a=b;
	b=c;
	if(c == num)
	{
		for(int i=2;i<=num/2;i++)
		{
			if(num%i == 0)
			{
				flag = 1;
				break;
			}
		}
	}
	if(c>num)
	{
		flag = 1;
		break;
	}
	
				
}
if(flag == 0)
	printf("Number %d is fibnocci prime\n",num);
else
	printf("Number %d is not fibnocci prime\n",num);
}
