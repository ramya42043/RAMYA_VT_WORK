#include<stdio.h>
int main()
{
char s[]="Hello world votarytech";
int i,j;
for(i=0;s[i];i++)
{
printf("%c",s[i]);
for(j=i+1;s[j];j++)
	printf("%c",s[j]);
printf("\n");
}
}
