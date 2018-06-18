#!/usr/bin/python
list1=[1,13,7,5,9]
print "list1 is : ",list1
l=len(list1)
for index in range(l):
	for index1 in range(index+1,l):
		if(list1[index]+list1[index1]) == 14:
			#print index,list1.index(index1)
			print "list1[{}] + list1[{}] = {}".format(index,index1,(list1[index]+list1[index1]))
