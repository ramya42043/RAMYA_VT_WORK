#include<stdio.h>
main()
{

printf("First: %d\n", __LINE__);
#line 0
printf("Second: %d\n", __LINE__);
printf("Third: %d\n", __LINE__);
}
