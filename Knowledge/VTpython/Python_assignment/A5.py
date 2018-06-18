#!/usr/bin/python
l=[1,2,3,4,5,6]
index=0
while(len(l)>0):
	index+=1
	l=l[-1:] + l[:-1]
	if(len(l)>index):		
		print "After rotation the list is :",l
		del(l[-index])
		print "After deletion the list is :",l
	else:
		if(len(l)==1):
			break	
		del(l[0])
		print "After deletion the list is :",l
print "Resultant list is ",l
