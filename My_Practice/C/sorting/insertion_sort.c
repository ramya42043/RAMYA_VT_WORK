#include<stdio.h>
void swap(int * a, int * b);
void printArray(int arr[], int size);
void insertion_sort(int * array, int n)
{
    int i = 0 , j = 0;
    int key;
    for(i = 1; i < n; i++)
    {
        key = array[i];
        j = i-1;
        while( j >= 0 &&  array[j] > key)
        {
            array[j+1] = array[j];
            j = j -1;
        }
        array[j+1] = key;
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
    //int arr[] = {0,1,2,3,4,5,6,7,8,9,10};
     int arr[] = {10,9,8,7,6,5,4,3,2,1,0};
    int n = sizeof(arr)/sizeof(arr[0]);
    printArray(arr, n);
    insertion_sort(arr, n);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
