#include<stdio.h>
int main()
{
	int a,i,b,flag =0;
	printf("enter a number:");
	scanf("%d",&a);
	for(i=0;i<=31;i++)
	{
		b=1<<i;	
		if(a == (a&b))
		{
			flag =1;
			break;
		}
	}
	if(flag ==1)
		printf("power of 2\n");
	else
		printf("not power of 2\n");
	

return 0;
}
