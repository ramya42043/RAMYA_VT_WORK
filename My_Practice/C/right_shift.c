#include<stdio.h>
main()
{
int n;
printf("enter a number:");
scanf("%d",&n);
for(int bit = 4;bit>=0;bit--)
printf("%d",(n>>bit)&1);
printf("\n");
printf("%d\n",(n>>1));
int r = n>>1;
for(int bit = 4;bit>=0;bit--)
printf("%d",(r>>bit)&1);
}
