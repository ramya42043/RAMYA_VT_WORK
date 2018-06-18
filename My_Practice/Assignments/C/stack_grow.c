#include<stdio.h>
int* foo(void)
{
	int b,*P=&b;
	printf("Address of local variable in function:%p\n",&b);
	return P;
}

int main()
{
int a;
printf("address of main local variable:%p\n",&a);
int *res = foo();
if(res < &a)
	printf("stack is growing down wards\n");
else
	printf("stack is growing upward\n");
return 0;
}

