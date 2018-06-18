#!/usr/bin/pyhton

num = input("enter")
num=num+1
list1=[]
list2=[]
for ind in range(1,num):
	list1.append(ind)
	list2.append(ind*ind)

print list1
print list2
dict1=dict(zip(list1,list2))
print dict1
