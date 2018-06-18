#include<stdio.h>
extern int val;
int  extern_function()
{
	val = 20;
	return val;
}
