count=0
def fun1(f):
	def new(*args,**kargs):		
		global count		
		print "decorators"
		count+=1
		for i in args:
			print i	
		print f(*args,**kargs)
		print count," time call"
	return new
@fun1
def add(a,b,c):
	return a+b+c

add(1,2,5)
add(1,2,5)
add(1,2,5)
add(1,2,5)
'''
def mul(a,b):
	return a*b

print mul(3,6)

def fub(*args,**kargs):
	return  args,kargs

print fub(1,2,3,s=6)
print fub(1)
print fub([1,2,3])
print fub(1,2,{"a":4})
print fub({"v":"k"})
'''

