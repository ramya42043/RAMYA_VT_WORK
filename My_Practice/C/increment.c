#include<stdio.h>
int reverse(int i)
{
if(i>5)
return 0;
else
 printf("%d ",i);
return reverse((i,i++));
}
int main()
{
int res = reverse(1);
//printf("main:%d\t",res);
return 0;
}

