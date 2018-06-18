#!/usr/bin/pyhton

class A(object):
	
	def fun1(self,x):
		self.x=x
		print "Class A fun1 method"
		
		
	def getxval(self):
		print self.x

class B(A):
	
	def fun(self):
		print "Class B fun1 method"
		#self.fun1()
			

obj=B()
obj.fun()
obj.fun1(100)
obj.getxval()

