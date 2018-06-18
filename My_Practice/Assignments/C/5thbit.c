#include<stdio.h>
main()
{
int num,i;
printf("enter a number:");
scanf("%d",&num);
for(i=31;i>=0;i--)
{
printf("%d",(num>>i)&1);
}
printf("\n");
((1<<5)&num)>0?printf("bit is 1\n"):printf("bit is 0\n");
}
