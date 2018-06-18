#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
	int arr[10],sum,i,j;
		srand(getpid());
	for(i=0;i<10;i++)
	{
		arr[i]=rand()%50;
		printf("%d ",arr[i]);
	}
	printf("\n");
	printf("enter sum");
	scanf("%d",&sum);
	for(i=0;i<10;i++)
	{
		for(j=i+1;j<10;j++)
		{
			if(arr[i]+arr[j]==sum)
			{
				printf("the pair is number1:%d index %d ,number2:%d index %d\n",arr[i],i,arr[j],j);
			}
		}
	}
	return 0;
}
