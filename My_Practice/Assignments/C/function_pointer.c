#include<stdio.h>
void test((*a))
{
(*a)(2,3);
}
void f(int a,int b)
{
printf("%d\n",a+b);
//return a+b;
}

int main()
{
test(&f);
//void (*fp)(int,int);
//fp = &f;
//(*fp)(2,3);
}
