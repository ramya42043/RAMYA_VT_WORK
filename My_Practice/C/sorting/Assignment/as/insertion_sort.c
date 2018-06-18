#include<stdio.h>
static void swap(int *, int *);

static void insertion_sort(int * arr, int n)
{
  int i = 0, j = 0, key =0;
  for(i = 1; i < n; i++)
  {
      j = i-1;
      key = arr[i];
      while(j >= 0 && arr[j] > key)
      {
          arr[j+1] = arr[j];
          j = j -1;
      }
      arr[j+1] = key;
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
    insertion_sort(arr, size);
    printf("Sorted Array: ");
    printArray(arr, size);

}
