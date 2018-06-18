#!/usr/bin/python
num=input("Enter Number to find the square numbers :\t")
while(num!=0):
	if((num>0)and(num<=2)):
		print "No numbers less than or equal 2 are square numbers\n"
	elif(num>2):
		for index in range(2,num):
			squr=index*index
			if(squr<=num):
				print "Result is\t",squr
	elif(num<0):
		print"Please enter +ve number only or 0 to exit\n"	
	num=input("Enter Number to find the square numbers :\t")
	
