#include <stdio.h>
void main()
{

	int arr1[] = {1, 5, 9, 10, 15, 20};
	int arr2[] = {2, 3, 8, 13,23,56,78};
	int arr3[200];
	int s1 = sizeof(arr1)/sizeof(arr1[0]);
	int s2 = sizeof(arr2)/sizeof(arr2[0]);
	int s3 = s1 + s2;
	int i=0, j=0, k=0;
	while(i<s1 && j<s2)
	{
		if(arr1[i]<arr2[j])
		{
			arr3[k]= arr1[i];
			k++;
			i++;

		}
		else
		{
			arr3[k] = arr2[j];
			k++;
			j++;
		}

	}
	while(i<s1)
	{
		arr3[k] = arr1[i];
		k++;
		i++;
	}
	while(j<s2)
	{
		arr3[k] = arr2[j];
		k++;
		j++;
	}


	printf("\nThe merged sorted array is :\n");
	for(i=0; i<s3; i++)
	{
		printf("%d   ", arr3[i]);
	}
	printf("\n");
}
