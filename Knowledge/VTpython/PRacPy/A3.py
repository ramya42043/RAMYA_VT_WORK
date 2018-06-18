#!/usr/bin/python
import math
num=input("please enter the number :\t")
count=0
index=1
while(count<num):
	count=0
	res=math.factorial(index)
	while(res!=0):
		rem=res%10
		if rem==0:
			count+=1
		else:
			break
		res/=10
	index+=1
if count==num:
	print "Result is ",index-1
else:
	print "No number who have contain {} trailing zero".format(num)
