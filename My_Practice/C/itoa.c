#include<stdio.h>
int main()
{
unsigned int hex = 0xABC123FF;
char hexString[256];
sprintf(hexString, "0x%X", hex);
printf("%s \n",hexString);
return 0;
}
