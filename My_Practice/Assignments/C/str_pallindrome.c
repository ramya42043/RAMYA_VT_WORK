#include<stdio.h>
#include<string.h>
int main()
{
char str[30],str1[30],temp;
int i,j,flag=0;
printf("enter a string:");
scanf("%s",str);
for(i=0,j=strlen(str)-1;i<j;i++,j--)
{
if(str[i]!=str[j])
{
	flag = 1;
	break;
}
}
if(flag==0)
printf("YES\n");
else
printf("NO\n");
/*strcpy(str1,str);
printf("%s",str1);
for(i=0,j=strlen(str)-1;i<j;i++,j--)
{
temp=str[i];
str[i]=str[j];
str[j]=temp;
}
printf("%s\n",str);
if((strcmp(str,str1))==0)
printf("string is pallindrome\n");
else
printf("string is not pallindrome\n");
*/
return 0;
}

