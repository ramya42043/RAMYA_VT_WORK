#include<stdio.h>
void swap(int *, int *);

 void selection_sort(int * arr, int n)
{
    int i = 0, j = 0, min_index = 0;
    for(i = 0; i < n; i++ )
    {
        min_index =i;
        for(j = i+1; j < n; j++)
        {
            if(arr[min_index] > arr[j])
                min_index = j;
        }
        swap(arr+i, arr+min_index);
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
/*void main(void)
{
    int arr[] = {10,9,8,7,6,5,4,3,2,1,0};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("Original Array: ");
    printArray(arr, size);
    selection_sort(arr, size);
    printf("Sorted Array: ");
    printArray(arr, size);

}*/
