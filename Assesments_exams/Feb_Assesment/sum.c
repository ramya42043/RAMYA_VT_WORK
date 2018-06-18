#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int fun(int arr[],int n)
{
	int i,j,sum=0,res=0;
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			res = arr[i]^arr[j];
			sum = sum+res;
		}
	}
	return sum;
}

int main()
{
	int arr[100],n,tc=0,i;
	int r[100];
	printf("enter number of test cases:");
	scanf("%d",&tc);
	int temp = tc;
	while(tc)
	{
		n=0;
		printf("number of elements:");
		scanf("%d",&n);
		printf("enter elements:");
		for(i=0;i<n;i++)
			scanf("%d",&arr[i]);
		int s = fun(arr,n);
		for(i=0;i<tc;i++)
			r[i]=s;
		tc--;
	}
	for(i=(temp-1);i>=0;i--)
		printf("%d\n",r[i]);
}
