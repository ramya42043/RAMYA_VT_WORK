#!/usr/bin/python
# Divide a number by 3 without using +, -, *, / or % operators. The number may be signed or unsigned. Note: Use bitwise operations only

def add(x,y):
	while(x):
		t = (x & y) << 1
		y ^= x
		x = t
	return y

def divideby3(num):
	sum1=0
	while(num > 3):
		sum1 = add(num >> 2,sum1)
		num = add(num >> 2,num & 3);
	if (num == 3):
		sum1 = add(sum1,1)	
	


	return sum1

num=input("enter the number to get div by 3\n")
result=divideby3(num)
print " {}/3 is {} ".format(num,result)
