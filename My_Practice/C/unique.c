#include<stdio.h>
int main()
{
int arr[]={1,2,3,4,5};
int arr2[]={2,1,4,5};
int i,j,sum1 = 0,sum2=0;
int size1 = sizeof(arr)/sizeof(arr[0]);
int size2 = sizeof(arr2)/sizeof(arr2[0]);
printf("%d \n",size1);
for(i=0;i<size1;i++)
	sum1 += arr[i];
for(j=0;j<size2;j++)
	sum2 += arr2[j];

printf("element is %d\n",sum1-sum2);
}
