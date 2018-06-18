#include<stdio.h>
int f1(int a)
{
	a++;
	printf("in f1 %d\n",a);
	return a;
}
int f2(int x)
{
	printf("in f2 :%d\n",x);
	return 0;
}
int main()
{
	int num=10;
	f2(f1(num));
	return 0;
}
