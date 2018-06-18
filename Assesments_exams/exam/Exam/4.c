#include<stdio.h>
void add(int num1,int num2)
{
	int res;
	res=num1+num2;
	printf("add is:%d\n",res);
}
void sub(int num1,int num2)
{
	int res;
	res=num1-num2;
	printf("sub is:%d\n",res);
}
void mul(int num1,int num2)
{
	int res;
	res=num1*num2;
	printf("mul is:%d\n",res);
}
void div(int num1,int num2)
{
	int res;
	res=num1/num2;
	printf("div is:%d\n",res);
}
int main()
{
	int num1,num2;
	printf("enter two nums:");
	scanf("%d%d",&num1,&num2);
	void (*ptr)(int,int);
	ptr=add;
	ptr(num1,num2);
	ptr=sub;
	ptr(num1,num2);
	ptr=mul;
	ptr(num1,num2);
	ptr=div;
	ptr(num1,num2);

}
