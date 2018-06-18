#include<stdio.h>
int main()
{
	unsigned int num,bit,count=0;
	printf("enter number:");
	scanf("%d",&num);
	while(num)
	{
		count += num&1;
		printf("%d",num&1);
		num>>=1;
//	printf("%d",(num>>1)&1);
	}
	printf("\n");
	printf("set bits is %d\n",count);
	return 0;
}
/*struct tag
{
double v4;
int v1;
char v2;
int v3;
int v5;
int v6;
}var;
int main()
{
printf("size=%d\n",sizeof(var));
return 0;
}*/

