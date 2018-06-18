#include<stdio.h>
int missing(int arr[],int n)
{
int i,total;
total = (n+1)*(n+2)/2;
int sum =0;
for(i=0;i<n;i++)
	sum += arr[i];
return total-sum;
}
int main()
{
int a[]={1,2,3,7,5,6,8,9,10};
int res = missing(a,9);
printf("%d\n",res);
}
