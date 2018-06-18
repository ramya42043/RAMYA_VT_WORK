#include<stdio.h>
#include<stdlib.h>
void func(int n);
void func1(int n);
static int step;
int main()
{
	int n;
	int i;
	printf("enter the number:");
	scanf("%d",&n);
	for(i=0;i<=5;i++)
	{
		func(n);
	printf("\n");
		func1(n);
	}
	printf("\n");
	return 0;
}
void func(int n)
{
	//static int step;
	//int step=0;
	printf("Step:%d\t",step);
	step=step+n;
	printf("%d\n",step);
}
void func1(int n)
{
	//static int step=0;
	//int step=0;
	printf("Step:%d  %s \t",step,__func__);
	//step=step+n;
	//printf("%d\n",step);
}
