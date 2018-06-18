#include<stdio.h>
#include<string.h>
int main()
{
	char str1[100],str2[100];
	int count=0;
	printf("enter main string:");
	scanf("%s",&str1[0]);
	printf("enter substring:");
	scanf("%s",&str2[0]);
	int len1 = strlen(str1);
	printf("len1=%d\t",len1);
	int len2 = strlen(str2);
	printf("len2:%d\n",len2);
	for(int i=0;i<=len1-len2;i++)
	{
		int j;
		for(j=0;j<len2;j++)
			if(str1[i+j] != str2[j])
				break;
			if(j==len2)
			{
				count ++;
				j=0;
			}
	}
printf("%s occrs %dtimes\n",str2,count);
}
