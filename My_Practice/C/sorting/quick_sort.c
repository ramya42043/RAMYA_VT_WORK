#include<stdio.h>
void swap(int * a, int * b);

int partition(int *array, int l, int r)
{
    int i = l, j = 0;
    int pivot = array[r];
    for(j = l; j < r; j++)
    {
        if(array[j] <= pivot)
        {
            swap(array+i, array+j );
            i++;
        }
    }
    swap(array+i, array+r);
    return i;
}


void quick_sort(int * array, int l, int r)
{
    if(l < r)
    {
        int pi = partition(array, l, r);
        quick_sort(array, l, pi-1);
        quick_sort(array, pi+1, r);
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
    //int arr[] = {0,1,2,3,4,5,6,7,8,9,10};
    //int arr[] = {10,9,8,7,6,5,4,3,2,1,0};
    int n = sizeof(arr)/sizeof(arr[0]);
    printArray(arr, n);
    quick_sort(arr, 0, n-1);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
