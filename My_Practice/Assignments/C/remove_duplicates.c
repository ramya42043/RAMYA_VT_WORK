#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main ()
{
	char str1[50] = {0};
	char *array;
	FILE *ifp,*ofp;
	FILE *baseifp;


	int i = 0,k=0,flag;
	ifp = fopen("myfile", "r");
	if(ifp==NULL)
		perror("input File is not open");
	ofp = fopen("outputfile", "w");
	if(ofp==NULL)
		perror("output File is not open");


	char * line = NULL;
	int len = 0;
	ssize_t read;
	while ((read = getline(&line, &len, ifp)) != -1) {
		printf("Retrieved line of length %zu :\n", read);
		printf("%s", line);
	}
	if (line)
		free(line);
	//fclose (ifp);
	ifp = freopen("myfile", "r", ifp);

	while(fscanf(ifp, "%s", str1)!=EOF)
	{
		printf ("%s\n",str1);
		flag = 0;
		array = (char *)malloc (strlen (str1)+1);
		strcpy(array,str1);

		if(i > 0)
			for (k = 0; k < i ; k++)
			{
				if (strcmp(array+k, str1)==0)
				{
					flag = 1;
					break;
				}
			}
		if (flag == 0)
		{
			fprintf(ofp, "%s ", str1);
		}
		i++;
		memset (str1, 0, 50);
	}
	printf ("\n");
	fclose(ifp);
	fclose(ofp);

	return 0;
}
