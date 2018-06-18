#include<stdio.h>
int main()
{
	int num;
	printf("enter a number:");
	scanf("%d",&num);
	//if(((num>>3)<<3)==num)
	printf("%d\n",(num&7));
	  if ((num&7) ==0)
	{
		printf("divisible\n");
	}
	else
		printf("no");

	return 0;
}
