#include<stdio.h>
main ()
{
union Test
{
unsigned int i;
unsigned char c[2];
};

union Test a = {300};
if(a.i=44)
{
 printf ("Littile enidan\n");
}
else
{
 printf ("BIG ENDIAN\n");
}
}
