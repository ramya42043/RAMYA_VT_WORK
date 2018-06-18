#include<stdio.h>
void swap(int * a, int * b);
void merge(int *arr, int l, int m, int r)
{
    int i = 0,j = 0,k = 0;
    int n1 = m - l + 1;
    int n2  = r - m;
    int L[n1],R[n2];
    for(i = 0; i < n1; i++)
        L[i] = arr[l+i];
    for(j = 0; j < n2; j++)
        R[j] = arr[m+j+1];
    i = 0;
    j = 0;
    k = l;
    while(i < n1 && j < n2)
    {
        if(L[i]<=R[j])
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
    while(i < n1)
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


void merge_sort(int * array,int l, int r)
{
    if(l < r)
    {
        int m = (l+r)/2;
        merge_sort(array, l , m);
        merge_sort(array, m+1, r);
        merge(array, l, m, r);
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
    merge_sort(arr, 0, n-1);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
