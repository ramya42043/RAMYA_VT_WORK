#include<stdio.h>
int main()
{
int num;
	while(1)
	{
		printf("enter a number:");
		scanf("%d",&num);
		if(num&1==1)
			printf("odd number\n");
		else
			printf("even number\n");
	}
return 0;
}
