#include<stdio.h>
#define get(name) #name
struct tag
{
char c;
int a;
}var;

int main()
{
	var.c=10; 
	int a;
	printf("enter a variable:");
	scanf("%d",&a);
	printf("variable is %d name is %s\n,struct variable is%s=%d",a,get(a),get(var.c),var.c);
	return 0;
}
