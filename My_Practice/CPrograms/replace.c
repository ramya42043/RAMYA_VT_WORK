#include<stdio.h>
 
int main()
{
    // Old file name
    char old_name[] = "1.c";
 
    // Any string
    char new_name[] = "sub.c";
    int value;
 
    // File name is changed here
    value = rename(old_name, new_name);
 
    // Print the result
    if(!value)
    {
        printf("%s", "File name changed successfully\n");
    }
    else
    {
        perror("Error");
    }
    return 0;
}
