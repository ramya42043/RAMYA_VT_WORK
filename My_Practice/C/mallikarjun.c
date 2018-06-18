#include<stdio.h>
int main()
{
int num,bit1,bit2,res;
printf("enter number,bit1,bit2 positions:");
scanf("%d,%d,%d",&num,&bit1,&bit2);
for(int i=31;i>=0;i--)
	printf("%d",(num>>i)&1);
int temp1 = ((num>>bit1)&1);
int temp2 = ((num>>bit2)&1);
printf("\ntemp1=%d temp2=%d\n",temp1,temp2); 
if(temp1 == temp2)
	return 0;
else
	{
		num ^= (1<<bit1);
		num ^= (1<<bit2);
	}

printf("res is %d\n",num);
for(int i=31;i>=0;i--)
	printf("%d",(num>>i)&1);
printf("\n");
}
