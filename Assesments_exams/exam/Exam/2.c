#include<stdio.h>
int main()
{
	int size1,size2;
	printf("enter size of arr1:");
	scanf("%d",&size1);
	printf("enter size of arr2:");
	scanf("%d",&size2);
	int arr1[size1],arr2[size2];
	int ind1,ind2,cnt=0;
	printf("enter values of arr1:");
	for(ind1=0;ind1<size1;ind1++)
		scanf("%d",&arr1[ind1]);
	printf("enter values of arr2:");
	for(ind1=0;ind1<size2;ind1++)
		scanf("%d",&arr2[ind1]);
	for(ind1=0;ind1<size2;ind1++)
	{
		for(ind2=0;ind2<size1;ind2++)
		{
			if(arr2[ind1]==arr1[ind2])
				break;
		}
		if(ind2==size1)
		{
			printf("arr2 is not a subset of arr1\n");
			return 0;
		}
	}
	printf("arr2 is subset of arr1\n");
	return 0;

}
