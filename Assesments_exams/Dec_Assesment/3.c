#include<stdio.h>
int invert(int x,int p,int n)
{
int i,num=x;
int cnt=0;
for(i=0;i<=31;i++)
{
	if(i==p)
		{
			for(int j=i;j<=31;j++)
			{
				num = (num^(1<<j));
				cnt++;
				if(cnt == n)
					break;
			}
		}
		
}
return num;
}
int main()
{
int num,pos,bits;
printf("enter number,position,bits:");
scanf("%d %d %d",&num,&pos,&bits);
int res = invert(num,pos,bits);
printf("resultant number is %d\n",res);
}
