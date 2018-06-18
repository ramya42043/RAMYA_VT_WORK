#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
printf("Process id is %d Parent:%d\n",getpid(),getppid());
return 0;
}
