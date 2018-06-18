#include<stdio.h>
#include<string.h>
int main()
{
char str[100],dict[1000],out_string[20];
int i,j,k=0;
printf("enter a dictionary of words:");
scanf("%[^\n]s",dict);
while(1)
{
printf("enter a string:");
scanf("%s",str);
for(i=0;i<=strlen(dict)-1;i++)
{
for(j=0;j<=strlen(str)-1;j++)
	{
	//if(strstr(str,dict))
	if(str[j]==dict[i])
		{
		for(k=i;dict[k]!=',';k++)
			{
			out_string[k] = dict[i];
			}
			out_string[k]=32;
		}
	}
}
printf("%s\n",out_string);
}
}	
		
	
