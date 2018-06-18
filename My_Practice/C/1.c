#include<stdio.h>
int main()
{
	int num,rev,rem,temp;
	printf("enter a number:");
	scanf("%d",&num);
	temp = num;
	while(temp)
	{
		rem = temp%10;
		rev = rev*10 +rem;
		temp =temp/10;
	}
	printf("the sum of integer and the reverse of integer is %d\n",num+rev);
	
	return 0;
}
