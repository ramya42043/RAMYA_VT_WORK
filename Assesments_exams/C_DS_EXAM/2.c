#include<stdio.h>
//array_subset.c
int main()
{
	int arr1[100],arr2[100],i=0,j=0,len1,len2,cnt=0;
	while(1)
	{
	printf("enter array1 length:");
	scanf("%d",&len1);
	printf("enter array2 length:");
	scanf("%d",&len2);
	printf("enter array1 elements:");
	for(i=0;i<len1;i++)
		scanf("%d",&arr1[i]);
	printf("enter array2 elements:");
	for(j=0;j<len2;j++)
		scanf("%d",&arr2[j]);
	
	for(i=0;i<len1;i++)
		{
			for(j=0;j<len2;j++)
				{
					if(arr1[i]==arr2[j])
						cnt++;
					
						
				}
		}
	if(cnt == len2)
		printf("arr2[] is subset of arr1[]\n");
	else
		printf("arr2[] is not subset of arr1[]\n");
	}
}
