#include<stdio.h>
#include<math.h>
int main()
{
int num,bit;
printf("enter number,bit:");
scanf("%d %d",&num,&bit);
int res = num *pow(2,bit);
printf("%d\n",res);
return 0;
}
