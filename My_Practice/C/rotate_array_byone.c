#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <unistd.h>

void rotate(int arr[], int n)
{
   int x = arr[n-1], i;
   for (i = n-1; i > 0; i--)
      arr[i] = arr[i-1];
   arr[0] = x;
}
 
int main()
{
    int arr[10], i;
    srand(getpid());
    printf("Given array is\n");
    for(i=0;i<7;i++)
    	{
    		arr[i]=rand()%50;
    		printf("%d ", arr[i]);
    	}
    rotate(arr, 7);
 
    printf("\nRotated array is\n");
    for (i = 0; i < 7; i++)
        printf("%d ", arr[i]);
 	printf("\n");
    return 0;
}
