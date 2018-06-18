#include<stdio.h>
#define MSB2LSBDW( x )  (\
              ( ( x & 0x000000FF ) << 24 ) \
            | ( ( x & 0x0000FF00 ) << 8 ) \
            | ( ( x & 0x00FF0000 ) >> 8 ) \
            | ( ( x & 0xFF000000 ) >> 24 ) \
             )
int main()
{
int x =0x12345678;
char *p;
int res = MSB2LSBDW(x);
printf("res : %x\n",res);
p=(char *) &res;
if(*p == 0x12 )
	printf("big endian\n");
else
	printf("little endian\n");

}
