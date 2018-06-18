#!/usr/bin/python
l = [1,13,7,5,9]
for i in range(0,len(l)):
	for j in range(1+i,len(l)):
		if l[i] + l[j] == 14:
			print i,j,l[i],l[j]
