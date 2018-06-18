#include<stdio.h>
int main()
{
int num,arr[100],i,j,temp=0;
printf("enter number of elements:");
scanf("%d",&num);
for(i =0;i<num;i++)
	scanf("%d",&arr[i]);
for(i=0;i<num;i++)
	printf("%d ",arr[i]);
	
printf("\n");
for(i=0;arr[i];i++)
{
	for(j=1;arr[j];j++)
	{
		if(arr[i]>arr[j])
		{
			temp =arr[i];
			arr[i]=arr[j];
			arr[j]=temp;
		}
	}
}
printf("after sorting\n");	
for(int k=0;k<num;k++)
	printf("%d",arr[k]);	
printf("\n");
}

