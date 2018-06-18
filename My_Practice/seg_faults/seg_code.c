#include<stdio.h>



int main()
{
int *p;
p = (int *)malloc(5);
p[0] = 4;
p[1] = 3;
p[2] = 4;
printf("asdfasdfjkasdl;f %d\n",p[0]);
printf("asdfasdfj343434kasdl;f\n");
printf("asdfasdfjk44444444444444asdl;f\n");
free(p);
free(p);
return 0;
}


