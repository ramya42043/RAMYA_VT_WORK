#include<stdio.h>
int main()
{
int num,bit;
printf("enter a number:");
scanf("%d",&num);
for(bit=31;bit>=0;bit--)
printf("%d",((num>>bit)&1));
printf("\n");
int res = (((num&0xAAAAAAAA)>>1) | ((num&0x55555555)<<1));
for(bit=31;bit>=0;bit--)
printf("%d",((res>>bit)&1));
printf("\n");
printf("integer %d\n",res);
return 0;
}
