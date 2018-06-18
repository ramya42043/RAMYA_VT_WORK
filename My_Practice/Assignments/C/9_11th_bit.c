#include<stdio.h>
int main()
{
short int a;
printf("enter a number:");
scanf("%hd",&a);
for(int bit=16;bit>=0;bit--)
printf("%d ",(a>>bit)&1);
printf("\n");
printf("9th bit is %d,11th bit before:%d\n",(a>>9)&1,(a>>11)&1);
int res = (~(1<<11))&a;
printf("11th bit is %d\n",(res>>11)&1);
}
