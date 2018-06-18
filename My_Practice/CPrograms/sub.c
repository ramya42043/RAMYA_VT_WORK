#include<stdio.h>
#include<string.h>
int main()
{
	char str[20]="sandaepdeepas",st[10]="deep",*temp;
	temp=str;
	int cnt=0;
	while((temp=strstr(temp,st)))
	{
		cnt++;
		temp++;
	}
	printf("%d\n",cnt);


}
