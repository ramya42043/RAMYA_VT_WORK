#include<stdio.h>
void divide(char *str)
{
	int j,count=0;

	for(int i=0;str[i];i++)
	{
		if(str[i]=='0')
		{
			count++;
		}
	}
	for(j=0;j<count;j++)
	{
		str[j]='0';
	}
	for(j=count;str[j];j++)
	{
		str[j]='1';
	}
}


int main()
{
	char str[]="0111110111100000";
	divide(str);
	printf("%s\n",str);
}
