#include<stdio.h>
int rightrotation(int num,int rot)
{
	num=num>>rot;
	return num;


}
int main()
{
	int num,rotations,res;
	printf("enter a num:");
	scanf("%d",&num);
	printf("enter no.of rotations:");
	scanf("%d",&rotations);
	res=rightrotation(num,rotations);
	printf("after rotation:%d\n",res);

}
