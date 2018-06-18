#!/us/bin/python
l = [1,13,7,5,9]
for i in range(len(l)):
	for j in range(i+1,len(l)):
		if l[i]+l[j] == 14:
			print i,j
