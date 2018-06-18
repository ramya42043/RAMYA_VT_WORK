#include<stdio.h>
int main()
{
  int i,j,k=6,l=13,m=16;
  for(i=1;i<=5;i++)
  {
    for(j=1;j<=5;j++)
    {
      if(i==1)
        printf("%-3d",j);
      else if(j==5)
        printf("%-3d",k++);
      else if(i==5)
        printf("%-3d",l--);
      else if(j==1)
        printf("%-3d",m--);
      else
        printf("   ");
    }
    printf("\n");
  }
  return 0;
}

