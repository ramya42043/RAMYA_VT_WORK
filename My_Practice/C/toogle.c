#include<stdio.h>
int main()
{
int n,bit,t;
printf("enter a number,bit:\n");
scanf("%d %d",&n,&t);
for(bit =31;bit>=0;bit--)
printf("%d",(n>>bit)&1);
printf("\n");
int res = (n^(1<<t));
for(bit =31;bit>=0;bit--)
printf("%d",(res>>bit)&1);
printf("\n");
return 0;
}


