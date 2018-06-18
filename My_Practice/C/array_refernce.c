#include<stdio.h>
int fun(int a[7],int n)
{
int i;
for(i=0;i<n;i++)
	printf("%d ",a[i]);
a[0]=10;
printf("\n");
return 0;
}

int main()
{
int arr[]= {1,2,3,4,5};
int size = sizeof(arr)/sizeof(arr[0]);
int res = fun(arr,size);
printf("%d\n",res);
for(int i=0;i<size;i++)
printf("%d ",arr[i]);
printf("\n");
}
