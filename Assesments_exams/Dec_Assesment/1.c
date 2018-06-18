#include<stdio.h>
#define MAX 5
int top=-1;
int cnt=0;
int push(int a[],int data)
{
	top++;
	if(top<MAX)
		a[top]=data;
	else
	{
		printf("stack overflow\n");
		top--;
	}
	cnt++;
	return cnt;
}
void display(int a[])
{
	int i;
	i=top;
	while(i!=-1)
	{
		printf("%d ",a[i]);
		i--;
	}
	
}
void middlenode(int a[])
{
	int i;
	i=top;
	while(i!=-1)
	{
		if(i == cnt/2)
		{
		printf("%d\n",a[i]);
		break;
		}
		i--;
	}
}

int main()
{
	int n,choice,data;
	int arr[MAX]; 
	push(arr,1);
	push(arr,2);
	push(arr,3);
	push(arr,4);
	push(arr,5);
	printf("stack elements are:");
	display(arr);
	printf("\nmiddle node data is:");
	middlenode(arr);
	}
