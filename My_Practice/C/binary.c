#include<stdio.h>
int main()
{
int num,count0=0,count1=0;
printf("enter a number:");
scanf("%d",&num);
while(num>0)
{
if(num%2==0)
	count0++;
else
	count1+=1;
num=num/2;
}
printf("number of zeros:%d\nnumber of 1s:%d\n",count0,count1);
}
