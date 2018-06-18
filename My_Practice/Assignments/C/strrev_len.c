#include<stdio.h>
int mystrlen(char *str)
{
int i;
for(i=0;str[i];i++);
return i;
}
void mystrrev(char *str)
{
int i,j;
char temp;
for(i=0,j=mystrlen(str)-1;i<j;i++,j--)
{
temp=str[i];
str[i]=str[j];
str[j]=temp;
}
return;
}

int main()
{
char str[30];
printf("enter a string:");
scanf("%s",str);
int res = mystrlen(str);
mystrrev(str);
printf("rev string:%s\n",str);
printf("length is:%d\n",res);
return 0;
}
