#!/usr/bin/python
count =0
count1 =0
s = raw_input("enter a string:")
for c in s:
	if c == '{' or c=='(' or c=='[':
		count += 1
	if c == '}' or c ==')' or c==']':
		count1 += 1
print count,count1
if count == count1:
	print True
else:
	print False
