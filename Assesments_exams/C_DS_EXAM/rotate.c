#include<stdio.h>
//rotate.c
int rightrotaions(int num,int rot)
{
	int n=0,rem,res;
	while(n<rot)
	{
		rem = num%10;
		num = num/10;
		num = rem*100+num;
		n++;
	}
	return num;
}
		
int main()
{
	int num,rotations;
	printf("enter number and rotations:");
	scanf("%d %d",&num,&rotations);
	int res = rightrotaions(num,rotations);
	printf("rotated number:%d\n",res);
}
