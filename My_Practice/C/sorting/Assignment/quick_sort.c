#include<stdio.h>
void swap(int *, int *);
int partition(int * array, int low, int high)
{
    int i = low;
    int pivot = array[high];
    for(int j = low; j < high; j++)
    {
        if(array[j] < pivot)
        {
            swap(array+j, array+i);
                    i++;
        }
    }
    swap(array+i, array+high);
    return i;
}
void quick_sort(int * array,int l, int r)
{
    if(l < r)
    {
        int pi = partition(array, l, r);
        quick_sort(array, l, pi-1);
        quick_sort(array, pi+1, r);
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
    quick_sort(arr, 0, size-1);
    printf("Sorted Array: ");
    printArray(arr, size);

}
