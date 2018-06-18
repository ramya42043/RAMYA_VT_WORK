#include<stdio.h>
int main()
{
int num1,num2,pos1,pos2,bit;
printf("pos1 must be greaterthan pos2\n");
printf("enter num1,num2 ,pos1,pos2:");
scanf("%d %d %d %d",&num1,&num2,&pos1,&pos2);
for(bit=pos1;bit>=pos2;bit--)
{
int bit1 = (num1>>bit)&1;
int bit2 = (num2>>bit)&1;
if(bit1==bit2)
continue;
else
{
num1 = num1^(1<<bit);
num2 = num2^(1<<bit);
}
}
printf("a=%d b=%d\n",num1,num2);
}
