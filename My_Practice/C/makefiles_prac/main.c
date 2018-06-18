#include<stdio.h>
int add(int,int);
int sub(int,int);
int main()
{
int v1,v2;
printf("enter valuess:");
scanf("%d %d",&v1,&v2);
int add_res=add(v1,v2);
printf("Addition result is %d\n",add_res);
int sub_res = sub(v1,v2);
printf("Subtraction result is %d\n",sub_res);
return 0;
}
