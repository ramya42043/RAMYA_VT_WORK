#include<stdio.h>
#include<string.h>
void sort(char *temp1)
{
	int i,j;
	char temp;
	for(i=0;i<strlen(temp1)-1;i++)
	{
		for(j=i+1;j<strlen(temp1)-1;j++)
		{
			if(temp1[i]>temp1[j])
			{
				temp =temp1[i];
				temp1[i]= temp1[j];
				temp1[j] =temp;
			}
		}
	}
}

int main()
{
	char str[100],str2[100],temp1[100],temp2[100],temp;
	printf("enter string1:");
	scanf("%s",str);
	printf("enter string2:");
	scanf("%s",str2);
	int i,j,count=0;
	strcpy(temp1,str);
	strcpy(temp2,str2);
	sort(temp1);
	sort(temp2);
	if(strcmp(temp1,temp2)==0)
	{
		for(i=0;i<strlen(str);i++)
		{
			if(str[i]==str2[i])
				count++;
		}
	}
	else 
	{
		printf("%d\n",-1);
		return 0;
	}
	printf("%d\n",count);
	return 0;
}
