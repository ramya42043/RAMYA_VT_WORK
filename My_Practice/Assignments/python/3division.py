#!/usr/bin/python
def add(x,y):
	while x:
		t = (x&y)<<1
		y^=x;
		x=t
	print y
	return y
num = input("enter a number")
def divide(num):
	sum_1 =0
	while num>3:
		sum_1 = add(num>>2,sum_1)
		num = add(num>>2,num&3)
	if num ==3:
		sum_1 =add(sum_1,1)
	print "sum:",sum_1
	return sum_1
divide(num)
