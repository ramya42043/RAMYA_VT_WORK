#!/usr/bin/python
cnt =0
cnt1 = 0
f = open('file.txt','r')
s = f.read()
for i in s:
	if i =='0':
		cnt += 1
	elif i == '1':
		cnt1 += 1 
print cnt,cnt1		

		
