#!/usr/bin/python

list1=[1,13,7,5,9]
size=len(list1)
#print size

for index1 in range(size):
	for index2  in range(index1+1,size):
		if 14==list1[index1]+list1[index2]:
			print "list1[{}]+list1[{}] = {} + {} = {}".format(index1,index2,list1[index1],list1[index2],list1[index1]+list1[index2])

	
