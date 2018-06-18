#include<stdio.h>
int main()
{
	int a,b,res;
	printf("enter a,b values:\n");
	scanf("%d %d",&a,&b);
	res= a|b;
	printf("BitwiseOR:%d\n",res);
	res= a&b;
	printf("BitwiseAND:%d\n",res);
	res= a||b;
	printf("Logical OR:%d\n",res);
	res= a&&b;
	printf("Logical AND:%d\n",res);
	return 0;
}

