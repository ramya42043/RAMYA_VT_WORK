#!/usr/bin/python
fd=open('file.txt','r')
str1=fd.read()
#str1=fd.readlines()
zero_count=0
one_count=0
for index in range(len(str1)):
	if str1[index]=='0':
		zero_count+=1
	elif str1[index]=='1':
		one_count+=1
print"Number of Zero in Given file is {}".format(zero_count)
print"Number of One in Given file is {}".format(one_count)
