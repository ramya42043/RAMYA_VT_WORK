#include<stdio.h>
int swap(int n)
{
return ((n&0x0000000F)<<28) | ((n&0xF0000000)>>28) |(n&0x0FFFFFF0) ;
}
int main()
{
unsigned int num;
printf("enter a number:");
scanf("%d",&num);
unsigned int res = swap(num);
for(int bit=31;bit>=0;bit--)
{
printf("%d",(num>>bit)&1);
}printf("\n");
for(int bit=31;bit>=0;bit--)
{
printf("%d",(res>>bit)&1);
}
printf("\n res is %u\n",res);
}
