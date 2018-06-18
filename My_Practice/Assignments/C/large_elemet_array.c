#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	int arr[100],lar,n,i,j;
	printf("enter number of elements:");
	scanf("%d",&n);
	srand(getpid());
	for(i=0;i<n;i++)
	{
		arr[i]=(rand()%100);
		printf("%d ",arr[i]);
	}
	printf("\n");
	lar = arr[0];
	for(i=0;i<n;i++)
	{
		if(arr[i]>lar)
		    lar=arr[i];
	}
	printf("largets element is %d\n",lar);
	return 0;
}

