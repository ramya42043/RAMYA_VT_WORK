import shutil
import os
import os.path

source = os.listdir('/home/paletmee/Desktop')

for files in source :
	print files

f1= open('/home/paletmee/Desktop/sample.py','w+')
f1.write("hello")
f1.read()
for line in f1 :

		print line


#f1.write("second line")
#f1=f1.read()
#for line in f1 : 
	#print l
f1.close()

st1 = "votar tech"
st2 = "tech"
st3 = "software tech"

if st1.find(st2):
		print "found"

		st1=st1.replace(st2,st3)

print st1

#**********************************************
import inflect
convert = inflect.engine()

key_in_dict=[]
values_in_dict = []

for i in range (1,101):

	values_in_dict.append(i)
	word = convert.number_to_words(i)
	key_in_dict.append(word)


dic = dict(zip(key_in_dict,values_in_dict))

for keys in dic :
	print keys
print type(dic)
print dic.items()
print dic.keys()
print dic.values()

lis= [1,13,7,5,9]

size = len(lis)

for index1 in range (size):
	for index2 in range (index1+1,size):
		if 14 == (lis[index1]+lis[index2]):
			print "lis[{}]+lis[{}] = {}+{} = {}".format(index1,index2,lis[index1],lis[index2],lis[index1]+lis[index2])
#**********************************************

from collections import Counter

lis = [1,0,1,0,1,1,1,0,0,1,0]
print Counter(lis)
ones = lis.count(1)
zeros = lis.count(0)
print ones ,zeros
#**********************************************

def add (x,y):
	while x:
		t = (x & y) <<1
		y ^= x
		x =t
	return y

def div3(num):
	sum1 = 0;
	while (num > 3):
		sum1= add(num >> 2 , sum1)
		num = add(num >>2, num & 3)
	if num == 3:
		sum1 = add(sum1,1)
	return sum1

num = input("enter the number")
res=div3(num)
print res


#**********************************************

lis = raw_input("enter the comma separated numbers").split(',')
print lis
print tuple(lis)

#**********************************************

class getipop(object):
	def __init__(self):
		self.s =""

	def getstr(self):
		self.s = raw_input("enter a string" )

	def putstrupr(self):
		print self.s.upper()

obj =  getipop()
obj.getstr()
obj.putstrupr()

#**********************************************

nums =[ int (val) for val in raw_input("enter two comma separted numbers").split(',')]
print nums

rows = nums[0]
colums = nums[1]

multidim = [[0 for col in range(colums)]for row in range(rows)]
print multidim
for i in range(rows):
	for j in range(colums):
		multidim[i][j] = i*j
print multidim

#**********************************************