#include<stdio.h>
//#include<string.h>
int my_strlen(char str[])
{
int i;
for(i=0;str[i];i++);
return i;
}
void my_strrev(char str[])
{
int i,j;
char temp;
for(i=0,j=my_strlen(str)-1;i<j;i++,j--)
{
str[i] ^= str[j];
str[j] ^= str[i];
str[i] ^= str[j];
/*temp =str[i];
str[i]=str[j];
str[j]=temp;*/
}
}
int main()
{
char str[100];
printf("enter a string:");
scanf("%s",str);
int res = my_strlen(str);
printf("String length is %d\n",res);
printf("before: %s\n",str);
my_strrev(str);
printf("after reverse: %s\n",str);
}
