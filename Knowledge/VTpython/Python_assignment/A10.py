#!/usr/bin/python
mylist=[1,2,3,4,5,6]
print"Iterate list using for loop"
for val in mylist:
	print val
print"Iterate list using iterator method"	
itr=iter(mylist)
for index in mylist:
	val=itr.next()
	print val,
print
mytuple=(7,8,9,10)
print"Iterate tuple using for loop"
for val in mytuple:
	print val
print"Iterate tuple using iterator method"	
itr=iter(mytuple)
for index in mytuple:
	val=itr.next()
	print val,
print 
str1="VOTARY"
print"Iterate str1 using for loop"
for letter in str1:
	print letter,
print
print"Iterate str1 using iterator method"	
str1 = "RAHUL CHATURVEDI"
itr = iter(str1)
len1=len(str1)
for index in range(len1):
	print itr.next(),
print
mydict={"name":"RAHUL","empid":839}
print"Iterate dictionary using for loop"
for val in mydict:
	print val,mydict[val]
print"Iterate dictionary using iterator method"
itr=iter(mydict)
for index in mydict:
	key=itr.next()
	print key,
	val=mydict[key]
	print val
