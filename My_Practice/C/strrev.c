#include<stdio.h>
#include<string.h>
main()
{
	char str[100],temp;
	int i,j,len;
	printf("enter a string:");
	scanf("%s",str);
	len = strlen(str);
	for(i=0,j=len-1;i<j;i++,j--)
	{
		temp = str[i];
		str[i] = str[j];
		str[j]= temp;
	}
	printf("after reversing %s\n",str);
}
