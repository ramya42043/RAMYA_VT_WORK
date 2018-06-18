#include<stdio.h>
#include<math.h>
unsigned int rev(int bit)
{
	unsigned int res=0;
	res = res + pow(2,bit);
	return res;
}
int main()
{
	unsigned int num,r;
	int i;
	printf("enter a number:");
	scanf("%d",&num);
	printf("num bits is:");
	for(i=31;i>=0;i--)
	{
		printf("%d",(num>>i)&1);
		if(((num>>i)&1)==1)
		{
			r = rev(31-i);
		}
	}
	printf("\n");
	printf("reversed number is : %u\n",r);
	printf("reversed number bits is: ");
	for(i=31;i>=0;i--)
	{
		printf("%u",(r>>i)&1);
	}
	printf("\n");

}
