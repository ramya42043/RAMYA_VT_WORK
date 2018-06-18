#include<stdio.h>
#include<string.h>
int anagram(char *s,char *t)
{
	int len1=strlen(s);
	int len2 = strlen(t);
	int c1 =0,c2 =0,i=0,j=0,k=0,flag=0;
	if(len1 ==len2)
	{
		for(i=0;i<len1;i++)
		{
			flag=0;
			for(k = 0;k<i;k++)
			{
				if(s[k] == s[i])
				{
					flag =1;
					break;
				}
			}
			if(flag ==1)
				continue;
			c1 =1;
			c2 =0;
			for(j=i+1;j<len1;j++)
			{
				if(s[j]==s[i])
					c1++;
			}
			for(j=0;j<len2;j++)
			{
				if(s[i] == t[j])
					c2++;
			}
			if(c1!=c2)
				return -1;
		}
		c1 =0;
		for(i=0;i<len1;i++)
		{
			if(s[i] == t[i])
				c1 +=1;
			
		}	
		return c1;
		}
	else
		return -1;
}


int main()
{
	char s[100],t[100];
	printf("enter string1:");
	scanf("%s",s);
	printf("enter string2:");
	scanf("%s",t);
	int res = anagram(s,t);
	printf("%d\n",res);
}	
