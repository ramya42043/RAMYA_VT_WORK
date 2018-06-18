#include<stdio.h>
static void swap(int *, int *);
static void merge(int *arr, int l, int m, int r)
{
    int i, j , k;
    int n1 = m-l+1;
    int n2 = r-m;
    int L[n1], R[n2];
    for(i = 0; i < n1; i++)
        L[i] = arr[l+i];
    for(i = 0; i < n2; i++)
        R[i] = arr[m+i+1];
    i = 0;
    j = 0;
    k = l;
    while(i < n1 && j < n2)
    {
        if(L[i] < R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while( i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while(j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
static void merge_sort(int * arr, int l, int r)
{
    if(l < r)
    {
        int m = (l+r)/2;
        merge_sort(arr, l, m);
        merge_sort(arr,m+1, r);
        merge(arr, l, m, r);
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
    merge_sort(arr, 0, size-1);
    printf("Sorted Array: ");
    printArray(arr, size);

}
