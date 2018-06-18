#include<stdio.h>
int fun(int num)
{

	if(num ==0)
		return 0;
	if(num<9)
		return -1;
	return (num>>3) -(num&7);
}
int main()
{
	int num;
	printf("enter a number:");
	scanf("%d",&num);
	int res= num;
	while(res>0)
	{
		res = fun(res);
	}
	if(res ==0)
		printf("divisible by 9\n");
	else
		printf("not divisble\n");
}

