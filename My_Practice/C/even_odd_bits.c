#include<stdio.h>
int main()
{
int num,i;
int even_arr[20],odd_arr[20];
int j=0,k=0;
printf("enter a number:");
scanf("%d",&num);
for(i=0;i<=31;i++)
{
	if(i%2==0)
		{
			even_arr[j]=(num>>i)&1;
		//	printf("%d",even_arr[j]);			
			j++;
		}
	else
		{
			odd_arr[k]=(num>>i)&1;
		//	printf("%d",(num>>i)&1);			
		//	printf("%d %d\n",odd_arr[k],k);			
			k++;
		}
}
printf("even bits are:");
for(j=0;even_arr[j];j++)
printf("%d",even_arr[j]);			
printf("\n");
printf("odd bits are:");
for(k=0;odd_arr[k];k++)
printf("%d",odd_arr[k]);
printf("\n");
}
