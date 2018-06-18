#include<stdio.h>
int invert(int num,int p,int n)
{
	int ind;
	for(ind=p;ind<=n;ind++)
	{
		num^=(1<<ind);

	}
	return num;
}
int main()
{
	int num,pos1,pos2,res;
	printf("enter number:");
	scanf("%d",&num);
	printf("enter pos1:");
	scanf("%d",&pos1);
	printf("enter pos2:");
	scanf("%d",&pos2);
	if(pos1>pos2)
		puts("pos1 must less than pos2");
	else
	{
		res=invert(num,pos1,pos2);
		printf("result is:%d\n",res);
	}

}
