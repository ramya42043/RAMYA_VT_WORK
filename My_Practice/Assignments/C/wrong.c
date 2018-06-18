#include <stdio.h>

char * fun(void)
{
  char c[] = "votarytech";
  char *p = c;
	 //c++;
  p++;
	printf("%p ",p);
  p[0]=65;
  p[5] = 65;
  return p;
}
int main()
{
 char* t =  fun();
 printf("\n%s\n", t);
}
