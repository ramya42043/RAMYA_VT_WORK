#include<stdio.h>
int myreversefunc(int num);
int main()
{

	int num = 1,res =0;
	if(*(char *)&num == 1)
	{
		printf("\nLittle-Endian\n");
	}
	else
	{
		printf("Big-Endian\n");
	}
	int a;
	printf("enter number to reverse:");
	scanf("%x",&a);
	res = myreversefunc(a);
	printf("reversed number is %d\n",res);
	return 0;
}

int myreversefunc(int num)
{
	int byte0, byte1, byte2, byte3;
	printf("coming number is %x\n",num);
	byte0 = (num & 0x000000FF) >> 0 ;
	printf("byte 0 :%d\t %d\n",byte0,(byte0 << 24));
	byte1 = (num & 0x0000FF00) >> 8 ;
	printf("byte 1 :%d\t %d\n",byte1,(byte1 << 16));
	byte2 = (num & 0x00FF0000) >> 16 ;
	printf("byte 2 :%d\t %d\n",byte2,(byte2 << 8));
	byte3 = (num & 0xFF000000) >> 24 ;
	printf("byte 3 :%d\t %d\n",byte3,(byte3 << 0));

	return((byte0 << 24) | (byte1 << 16) | (byte2 << 8) | (byte3 << 0));
} 
