#include<stdio.h>
static void swap(int *, int *);
static int partition(int * arr, int low, int high)
{
    int pivot =arr[high];
    int i = low;
    for(int j = low; j < high; j++)
    {
        if(arr[j] < pivot)
        {
            swap(arr+i, arr+j);
            i++;
        }
    }
    swap(arr+i, arr+high);
    return i;
}
static void quick_sort(int *arr, int l, int r)
{
    if(l < r)
    {
        int pi = partition(arr, l, r);
        quick_sort(arr, l, pi-1);
        quick_sort(arr, pi+1, r);

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
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("Original Array: ");
    printArray(arr, size);
    quick_sort(arr, 0, size-1);
    printf("Sorted Array: ");
    printArray(arr, size);

}
