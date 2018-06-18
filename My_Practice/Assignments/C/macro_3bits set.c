#include<stdio.h>
#define set(n,p) n|(7<<p)
int main()
{
int num,pos,bit;
printf("enter number,pos:");
scanf("%d %d",&num,&pos);
for(bit=31;bit>=0;bit--)
printf("%d",(num>>bit)&1);
int res = set(num,pos);
for(bit=31;bit>=0;bit--)
printf("%d",(res>>bit)&1);
printf("\n");
printf("%d\n",res);
}
