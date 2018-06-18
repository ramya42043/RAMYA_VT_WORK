#include<stdio.h>
#include<string.h>
int main()
{
char str[100];
int i,j,res,res1,s=0;
int flag=0;
printf("enter a string:");
scanf("%s",str);
printf("%s\n",str);
for(i=0;i<=strlen(str)-1;i++)
{	res = (str[i]-48);
	res1 = (str[i+1]-48);
	if(res+res1 == (str[i+2]-48))
		flag=1;
		
}
if(flag==1)
printf("given string is sum string\n");
else
printf("given string is not sum string\n");

}
