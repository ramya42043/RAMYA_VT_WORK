#include <stdio.h>
#define MAXSIZE 5
void main()
{
    int array[MAXSIZE];
    int i, j, num, temp;
    printf("Enter the elements one by one \n");
    for (i = 0; i < MAXSIZE; i++)
    {
        scanf("%d", &array[i]);
    }
    printf("Input array is \n");
    for (i = 0; i < MAXSIZE; i++)
    {
       printf("%d\n", array[i]);
    }
    /*   Bubble sorting begins */

    for (i = 0; i < MAXSIZE; i++)
    {
        for (j = 0; j < (MAXSIZE - i - 1); j++)
        {
           if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
       }
    }
    printf("Sorted array is...\n");

    for (i = 0; i < MAXSIZE; i++)
    {
        printf("%d\n", array[i]);
    }
}
