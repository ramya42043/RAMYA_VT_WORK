#include<stdio.h>
void swap(int *, int *);
void merge(int *array, int l, int m, int r)
{
    int i = 0, j = 0, k = 0;
    int n1 = m-l+1;
    int n2 = r -m;
    int L[n1], R[n2];
    for(i = 0; i < n1; i++)
        L[i] = array[l+i];
    for(i = 0; i < n2; i++)
        R[i] = array[m+i+1];
    i = 0;
    j = 0;
    k = l;
    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j] )
        {
            array[k] = L[i];
            i++;
        }
        else
        {
            array[k] = R[j];
            j++;
        }
        k++;
    }
    while( i < n1)
    {
        array[k] = L[i];
        k++;
        i++;
    }
    while( j < n2)
    {
        array[k] = L[j];
        k++;
        j++;
    }
}

void merge_sort(int * array, int l, int r)
{
    if(l < r)
    {
        int m = (l + r) /2;
        merge_sort(array, l, m);
        merge_sort(array, m+1, r);
        merge(array, l, m, r);
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
    merge_sort(arr, 0, size-1);
    printf("Sorted Array: ");
    printArray(arr, size);

}
