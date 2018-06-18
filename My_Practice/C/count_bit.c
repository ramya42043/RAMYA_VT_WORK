#include<stdio.h>
int fun(int num,int start,int end)
{
int mask=0,i;
for(i=start;i<=start+end;i++)
{
	mask |= 1<<i;
}
printf("%x\n",mask);
return num&mask;
}
int main()
{
int num,mask=0;
printf("enter number:");
scanf("%x",&num);
int res = fun(num,8,8);
printf("result is %x\n",res);
}
