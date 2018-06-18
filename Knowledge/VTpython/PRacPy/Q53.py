#!/usr/bin/python
import inflect
num=input("please enter the number : ")
dict1={}
list1=[]
list2=[]
obj=inflect.engine()
for index in range(1,num+1):
	dict1[index]=obj.number_to_words(index*index)
	'''
	list1.append(index)
	list2.append(obj.number_to_words(index*index))
	dict1=dict(zip(list1,list2))
	'''
print dict1.items()
