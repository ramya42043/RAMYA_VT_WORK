#include<stdio.h>
void swap(int * a, int * b);
void printArray(int arr[], int size);
void bubbleSort(int * array, int n)
{
    int i = 0, j = 0;
    int swaps =0;
    for(i = 0; i<n-1; i++)
    {
        swaps = 0;
        for(j = 0; j< n-i-1; j++)
            if(array[j]>array[j+1])
            {
            swap(array+j, array+j+1);
            swaps =1;
            printArray(array,n);
            }
        if(swaps == 0)
        {
            printf("break\n");
            break;
        }
    }

}
void swap(int * a, int * b)
{
    int temp = *a;
    *a = *b;
    *b = temp;

}
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int main()
{
   // int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int arr[] = {1,2,8,4,5,6,7,8,9,10};
    int n = sizeof(arr)/sizeof(arr[0]);
    printArray(arr, n);
    bubbleSort(arr, n);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
