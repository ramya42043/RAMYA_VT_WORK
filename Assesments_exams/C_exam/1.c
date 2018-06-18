#include<stdio.h>
int main()
{
int num,i,j,flag=0,count =0;
printf("enter which position prime number you want:");
scanf("%d",&num);
for(i=2;;i++)
{
	flag =0;
	for(j=2;j<=i/2;j++)
	{
		if(i%j == 0)
		{
			flag = 1;
			break;
		}
	}
	if(flag == 0)
		count ++;
	if(count == num)
		break;
}
printf("prime number in position %d is: %d\n",num,i);
}
	
	
	
