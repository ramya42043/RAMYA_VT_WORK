#include<stdio.h>
#include<string.h>
int main()
{
char str[100];
int i,j;
printf("enter a string:");
scanf("%s",&str[0]);
int len=strlen(str);
for(i=0,j=len-1;i<j;i++,j--)
{
	if((str[i]==str[j]) && str[i]!='*')
	{
		continue;
	}
	else if((str[i]==str[j]) && str[i] == '*')
	{
		str[i]='a';
		str[j]='a';
		continue;
	}
	else if(str[i]=='*')
	{
		str[i]=str[j];
		continue;
	}
	else if(str[j]=='*')
	{
		str[j]=str[i];
		continue;
	}
	else
	{
		printf("not possible\n");
		return 0;
	}
		
}
printf("string is:%s\n",str);
}
		
