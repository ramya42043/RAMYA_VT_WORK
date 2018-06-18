#include<stdio.h>
struct data
{
        int val;
        short int num;
	float f;
        char name[10];

}size;
int main()
{
        struct data *ptr=NULL;
        ptr++;
        printf("%d\n",ptr);
}
