#include<stdio.h>
int main()
{
int a,b;
printf("enter a,b");
scanf("%d %d",&a,&b);
if(!(a^b))
   printf("equal\n");
else
   printf("not equal\n");
}
