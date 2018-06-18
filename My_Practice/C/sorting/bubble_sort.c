#include<stdio.h>
void swap(int * a, int * b);
void bubbleSort(int * array, int n)
{
    int i = 0, j = 0;
    for(i = 0; i<n-1; i++)
    {
        for(j = 0; j< n-i-1; j++)
            if(array[j]>array[j+1])
            swap(array+j, array+j+1);
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
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);
    printArray(arr, n);
    bubbleSort(arr, n);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
