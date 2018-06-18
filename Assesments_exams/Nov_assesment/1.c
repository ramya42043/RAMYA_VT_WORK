#include<stdio.h>
#include<unistd.h>
int main()
{
	if(fork())
	{
	printf("hello ");
	}
	else
	printf("world\n");

}
