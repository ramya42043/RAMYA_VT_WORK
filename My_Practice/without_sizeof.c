#include<stdio.h>
int main()
{
	int var,size;
	size = (&var+1);
	int s= &var;
	int res= size-s;
	printf("%d %d %d\n",size,s,res);
}
