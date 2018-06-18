#!/usr/bin/pyhton

number=input("enter the number")
list1=[]
list2=[]
for num in range (1,number+1):
	list1.append(num)
	list2.append(num*num)
dic={}
dic=dict(zip(list1,list2))
print dic

for key in dic:
	print key
for val in dic.itervalues():
	print val
for d in dic.iteritems():
	print d

print dic.items()
print dic.values()
print dic.keys()
