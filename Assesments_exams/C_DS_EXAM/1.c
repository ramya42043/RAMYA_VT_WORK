#include<stdio.h>
//rightrotation.c
int rightrotation(int number,int rot)
{
	return number>>rot;
}
int main()
{
	int num,rotations;
	printf("enter number,rotations:\n");
	scanf("%d %d",&num,&rotations);
	int res = rightrotation(num,rotations);
	printf("rotated number = %d\n",res);
}
