#include<stdio.h>
int fun(int n)
{
	int rem,count=0;
	while(n)
	{
		rem = n%10;
		count++;
		n = n/10;
	}
	return count;
}
int arm_strong(int num,int pow)
{
	int rem,sum=0,mul=1;
	while(num)
	{
		rem = num%10;
		mul=1;
		for(int i=0;i<pow;i++)
		{
			mul= mul*rem;
		}
		sum += mul;
		num = num/10;
	}
	return sum;
}
int main()
{
	int num1,num2;
	printf("enter a number ranges:");
	scanf("%d %d",&num1,&num2);
	//for(int i= num1;i<=num2;i++)
	//		{
			int res = fun(num1);
			res= arm_strong(num1,res);
			if(num1 == res)
			printf("arm strong %d\n",num1);
			//}
			return 0;
			}
