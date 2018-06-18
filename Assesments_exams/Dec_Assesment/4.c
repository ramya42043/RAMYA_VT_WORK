#include<stdio.h>
int main()
{
	int arr[]={1,2,3,4,1,2,3,4,5,6},arr1[100];
	int i,j,k;
	int size = sizeof(arr)/sizeof(arr[0]);
	printf("size = %d\n",size);
	for(i=0;i<=size;i++)
	{
		for(j=i;j<=size;j++)
		{
			if(arr[i]==arr[j])
			{
				for(j=i;j<=size;j++)
				{
					arr1[k] = arr[j];
					printf("%d",arr1[k]);
				}
			}
			else
				continue;
		}
		//printf("%d",arr[i]);
	}
}

//for(i=0;arr[i];i++)



