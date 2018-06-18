#include<stdio.h>
int main()
{
int num,res,i,temp =0;
printf("enter a number:");
scanf("%d",&num);
while(num)
{
res = (num%2);
printf("%d",res);
num=num/2;
}

return 0;
}
