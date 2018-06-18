#include<stdio.h>
void swap(int *, int *);

void insertion_sort(int * array, int n)
{
    int i = 0, j = 0, key = 0;
    for(i = 1; i < n ; i++)
    {
        key = array[i];
        j = i -1;
        while( j >= 0 && array[j] > key)
        {
            array[j+1] = array[j];
            j = j - 1;
        }
        array[j+1] = key;
    }
}


void swap(int *a, int * b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void printArray(int * array, int n)
{
    int i = 0;
    for(i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
void main(void)
{
    int arr[] = {10,9,8,7,6,5,4,3,2,1,0};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("Original Array: ");
    printArray(arr, size);
    insertion_sort(arr, size);
    printf("Sorted Array: ");
    printArray(arr, size);

}
