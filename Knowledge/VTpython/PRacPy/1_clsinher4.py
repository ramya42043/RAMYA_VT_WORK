#!/usr/bin/pyhton

class A(object):
	__count =10
	def fun1(self,x):
		print "Class A fun1 method"
		self.x=x
		print self.__count
	def getxval(self):
		print self.x
	
class B(A):

	#super(B,self).fun1()
	
	def fun1(self):
		print "Class B fun1 method"
		#self.fun1()
		print self.__count
	




obj=A()
obj.fun1(100)
obj.getxval()

	
