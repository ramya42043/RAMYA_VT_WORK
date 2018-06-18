#include<stdio.h>
int main()
{
int n;
printf("enter number:");
scanf("%d",&n);
int res=(((n&0xAAAAAAAA)>>1)|((n&0x55555555)<<1));
printf("res= %d\n",res);
return 0;
}
