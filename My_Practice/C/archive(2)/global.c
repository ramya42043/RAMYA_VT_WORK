#include<stdio.h>
int val=10;
int extern_function();
int main()
{
	printf("%d\n",val);
  	int res = extern_function();
	printf("res = %d\n",res);
	return 0;
}
	
