#include<stdio.h>
int main()
{
	int data,bit,count =0;
	printf("enter a number:\n");
	scanf("%d",&data);
	while(data)
	{
		count += data &1;
		data >>= 1;
	}
	printf("number of set bits is %d\n",count);
	return 0;
}
