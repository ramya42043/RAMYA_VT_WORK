#include<stdio.h>
#include<string.h>
int main()
{
	char s[]="Hello";
	int i,j,l;
	int len = strlen(s);
	printf("Length is %d\n",len);

	for(i=1;i<=len;i++)
	{
		for(j=0;j<=len-i;j++)
		{
			int k= j+i-1;
			for(l=j;l<=k;l++)
				printf("%c",s[l]);
			printf("\n");
		}
	}
}
