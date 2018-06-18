#include<stdio.h>

int main()
{
int i,j,sum=0,count;
for(i=1;i<=100;i++)
{
if(i%2 !=0)
{
	sum += i;
	count ++;
}
}
printf("sum is %d average is %d \n",sum,sum/count);
}


/*int i,j,count=0,avg,sum=0,flag =1;;
for(i =2;i<=100;i++)
{
flag =1;
for(j=2;j<=i/2;j++)
{	
	if(i%j == 0)
	{
		flag =0;
		break;
	}
}
if(flag ==1)
{
sum =sum+i;
count ++;
}
//printf("%d ",i);
}
printf("sum is %d average is %d\n",sum,sum/count);
*/

