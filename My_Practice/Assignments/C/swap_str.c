#include<stdio.h>
#include<string.h>

char* swap(char* str)
{
    int end = strlen(str) - 1;
    int start = 0;

    while (start < end)
    {
        str[start] ^= str[end];
        str[end] ^= str[start];
        str[start] ^= str[end];
        ++start;
        --end;
    }

    return str;
}
int main()
{
char str[100];
printf("enter a string:");
scanf("%s",str);
swap(str);
printf("%s\n",str);
return 0;
}
