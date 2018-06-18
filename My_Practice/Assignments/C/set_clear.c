#include<stdio.h>
int main()
{
        int a,bit,i;
        printf("enter a number");
        scanf("%d",&a);
        for(i=31;i>=0;i--)
                printf("%d",(a>>i)&1);
	printf("\n");
        printf("enter bit position:");
        scanf("%d",&bit);
        printf("============clear operation==========\n");
        int res = (a&(~(1<<bit)));
        for(i=31;i>=0;i--)
                printf("%d",(res>>i)&1);
         printf("\n");
         printf("\n=============set operation=========\n");
         printf("enter bit position:");
         scanf("%d",&bit);
         res = (1<<bit)|a;
         for(i=31;i>=0;i--)
                printf("%d",(res>>i)&1);
          printf("\n");
          

}
