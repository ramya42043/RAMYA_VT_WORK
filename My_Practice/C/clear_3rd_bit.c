#include<stdio.h>
int main()
{
int num,bit;
printf("enter number:");
scanf("%d",&num);
for(bit=31;bit>=0;bit--)
	printf("%d",(num>>bit)&1);
printf("\n");
int res = (~(1<<3))&num;
for(bit=31;bit>=0;bit--)
	printf("%d",(res>>bit)&1);
printf("\n");
return 0;
}

