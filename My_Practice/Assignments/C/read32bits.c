#include<stdio.h>
int main()
{
int num;
printf("enter a number:");
scanf("%d",&num);
char *var = (char*)&num;
for(int i=3;i>=0;i--)
printf("%d ",*(var+i));
}
