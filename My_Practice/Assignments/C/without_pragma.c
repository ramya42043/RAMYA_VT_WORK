#include<stdio.h>
struct tag
{
int a;
char b;
float c;
}__attribute__((packed));
int main()
{
struct tag var;
printf("size is %lu\n",sizeof(var));
}
