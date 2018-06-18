#include<stdio.h>
int main()
{
int* a;
if(sizeof(int *) == 8)
printf("operating system is 64-bit\n");
else
printf("32-bit\n");
return 0;
}
