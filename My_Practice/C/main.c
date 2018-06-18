#include<stdio.h>
main()
{
int a,b,res;
printf("enter a,b values:");
scanf("%d %d",&a,&b);
res = add(a,b);
printf("adding result is %d\n",res);
res = sub(a,b);
printf("sub result is %d\n",res);
}
