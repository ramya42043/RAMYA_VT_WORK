#!/usr/bin/python
#Divide a number by 3 without using +, -, *, / or % operators. The number may be signed or unsigned. Note: Use bitwise operations only
def add(var,var1):
	while(var):
		temp= (var & var1) << 1
		var1^=var
		var=temp
	return var1

def divideby3(num):
	res=0
	while(num>3):
		res=add(num>>2,res)
		num=add(num>>2,num&3)
	if(num==3):
		res=add(res,1)
	return res

num=input("Please enter number :\t")
result=divideby3(num)
print "Result is ",result
