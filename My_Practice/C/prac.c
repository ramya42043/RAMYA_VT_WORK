#include<stdio.h> 
int main( )
{
    void *vp;
    char ch = 'g', *cp = "goofy";
    int j = 20;
    vp = &ch;
    printf("%c\n", *(char *)vp);
    vp = &j;
    printf("%d\n",*(int *)vp);
    vp = cp;
    printf("%s\n",(char *)vp + 3);
    return 0;
}
