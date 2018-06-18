#!/usr/bin/python
fd1 = open('file1.txt', 'r')
fd2 = open('file2.txt', 'r')
data=fd2.readlines()
for i in fd1:
	if i not in data:
            print i,

fd1.close()
fd2.close()
