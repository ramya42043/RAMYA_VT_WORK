#include<stdio.h>
#include<string.h>
 
int isHeterogram(char s[], int n)
{
    printf("n= %d\n",n);
    int hash[26] = { 0 };
     
    for (int i = 0; i < n; i++)
    {
        if (s[i] != ' ')
        {
            if (hash[s[i] - 'a'] == 0)
                hash[s[i] - 'a'] = 1;
                 
            else
                return 0;
        }
    }
     
    return 1;
}
 
int main()
{
    char s[100]; 
    printf("enter string:");
    scanf("%[^\n]s",&s[0]);
    int n = strlen(s);
    int res = isHeterogram(s, n);
    printf("res = %d\n",res);
    if(res == 0)
	printf("%s is not a heterogram\n",s);
    else
	printf("%s is a heterogram\n",s);
    return 0;
} 
