#include<stdio.h>
#include<string.h>
int main()
{
char str[100],temp,t[50],flag=0,res;
int i,j,count=1,len=1;
printf("enter a string:");
scanf("%s",str);
for(i=0;i<strlen(str);i++)
{
	count =1;
	for(j=i+1;j<strlen(str);j++)
	{
		if(str[i] == str[j])
		{
		++count;
		}
		else
			break;
	}		
	if(len<count)
		len  = count;		
}

printf("%d\n",len);
}








































