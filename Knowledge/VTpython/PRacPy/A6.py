#!/usr/bin/python
import math
product=1
count=1
list1=[]
num=input("Please enter the start number:\t")
num1=input("Please enter the end number:\t")
for index in range(num,num1+1):
	v1=int(math.sqrt(index))
	if(index>1):
		for index1 in range(2,v1+1):
			if(index%index1==0):
				count=0
				break
		else:
			list1.append(index)
			product*=index
if(count!=0):
	print"one"
else:
	print "The prime number between {} and {} is {}".format(num,num1,list1)
	print "And product is ",product
print "Thanks\n"
