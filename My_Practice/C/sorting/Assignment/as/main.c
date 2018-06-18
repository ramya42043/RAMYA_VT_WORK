#include<stdio.h>
void main(void)
{
    int arr[] = {10,9,8,7,6,5,4,3,2,1,0};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("Original Array: ");
    printArray(arr, size);
    selection_sort(arr, size);
    printf("Sorted Array: ");
    printArray(arr, size);

}
