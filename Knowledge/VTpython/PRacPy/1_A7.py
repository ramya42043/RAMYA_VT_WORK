#!/usr/bin/python
import math
num=input("please enter the number\n")
v1=1
while(v1<=num):
	fact=math.factorial(v1)	
	if(fact%num == 0):
		print "The required number is ",v1," Whose factorial is  ",fact,"divisibal by ",num
		print "The required number is {} Whose factorial is {} divisibal by {} ".format(v1,fact,num)
		break
	else:
		v1+=1
print "End of the program\n"
