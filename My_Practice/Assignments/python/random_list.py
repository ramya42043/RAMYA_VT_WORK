#!/usr/bin/python
import random
c=[]
a=[]
b=[]
for i in range(0,10):
    i = random.randint(0,10)
    a.append(i)
print a
for j in range(0,10):
    j = random.randint(0,10)
    b.append(j)
print b
lena=len(a)
lenb=len(b)
if lena>=lenb:
   for i in range(lenb):
      if b[i] in a and b[i] not in c:
         c.append(b[i])
else:
   for i in range(lena):
      if a[i] in b and a[i] not in c:
         c.append(a[i])
print c
