#include<stdio.h>
void swap(int *, int *);

static void bubble_sort(int * array, int n)
{
    int i = 0, j = 0, swaps=0;
    for(i = 0; i < n; i++ )
    {
        swaps = 0;
        for(j = 0; j < n-i-1; j++)
        {
            if(array[j] > array[j+1])
            {
                swap(array+j, array+j+1);
                swaps =1;
            }
        }
        if(swaps == 0)
            break;
    }

}


static void swap(int *a, int * b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
static void printArray(int * array, int n)
{
    int i = 0;
    for(i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
static void main(void)
{
    int arr[] = {10,9,8,7,6,5,4,3,2,1,0};
    //int arr[] = {1,2,3,4,5,6,7,8,9};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("Original Array: ");
    printArray(arr, size);
    bubble_sort(arr, size);
    printf("Sorted Array: ");
    printArray(arr, size);

}
