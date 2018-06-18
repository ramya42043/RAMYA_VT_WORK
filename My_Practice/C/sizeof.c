#include<stdio.h>
struct 
{
int a;
char b;
}var;

int main()
{
	//int var,size;
	//ptr = &var;
	//ptr = ptr+1;int res ;
	int size = (&var+1);
	int s= &var;
	int res= size-s;
	printf("%d %d %d\n",size,s,res);
}                                                                                                                                                                                                                                                                                              
