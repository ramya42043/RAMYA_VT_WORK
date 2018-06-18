#include<stdio.h>
int main()
{
int n,l,r,bit;

printf("enter a number,bit ranges:");
scanf("%d %d %d",&n,&l,&r);
for(bit=l-1;bit<=r-1;bit++)
	n = n|(1<<bit);
printf("%d\n",n);
return 0;
}
