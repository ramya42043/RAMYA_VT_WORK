#include <stdio.h>

int main()
{
    long n = 39714, i=1;
    for(i=10;i<n;i*=10);

    for (i=i/10; n>0; i/=10)
    {
        printf("%ld\n", n);
        n%=i;
    }

    return 0;
}
