#!/usr/bin/python
mylist=[]
num=input("Please enter the numbers or 0 to exit : ")
while(num!=0):
	mylist.append(num)
	num=input("Please enter the numbers or 0 to exit : ")
print mylist
len1=len(mylist)
index=0
num=0
print len1
while(num<len1):
	if(mylist[index]<0):
		ele=mylist.pop(index)
		print ele
		mylist.append(ele)
		print "\n",mylist
		index -=1
	num +=1
	index +=1
print "Given list is : ",mylist

