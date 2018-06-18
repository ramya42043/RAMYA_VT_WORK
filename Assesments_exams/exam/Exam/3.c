#include<stdio.h>
int main()
{
	int arr[10],res[10],ind1,ind2,cnt=0;
	puts("enter values into array:");
	for(ind1=0;ind1<10;ind1++)
		scanf("%d",&arr[ind1]);
	for(ind1=0;ind1<10;ind1++)
	{
		for(ind2=0;ind2<10;ind2++)
		{
			if((arr[ind1]==arr[ind2])&&(ind1!=ind2))
				break;
		}
		if(ind2==10)
			res[cnt++]=arr[ind1];
	}	
	puts("resultant arr is:");
	for(ind1=0;ind1<cnt;ind1++)
		printf("%d ",res[ind1]);
	printf("\n");
}
