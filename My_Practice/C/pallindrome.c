#include<stdio.h>
int main()
{
unsigned int num,d,rev=0;
printf("enter a number:");
scanf("%d",&num);
int temp=num;
while(num)
{
d = num%10;
rev = rev*10+d;
num = num/10;
}
if(temp == rev)
	printf("pallindrome\n");
else
	printf("not pallindrome\n");
return 0;
}
