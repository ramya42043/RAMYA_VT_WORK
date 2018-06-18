#include<stdio.h>
int main()
{
int a,b,bit,temp;
printf("enter a,b:");
scanf("%d %d",&a,&b);
for(bit=31;bit>=0;bit--)
{
int bit1 = (a>>bit)&1;
int bit2 = (b>>bit)&1;
if(bit1==bit2)
continue;
else
{
a = a^(1<<bit);
b = b^(1<<bit);
}
}
printf("a=%d b=%d\n",a,b);
}
