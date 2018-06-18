#!/usr/bin/python

class A(object):

	def fun1(self):
		print "A class func1 method"
	def fun2(self):
		print "A class func2 method"
class B(A):
	#super(B,self).fun1()
	def fu(self):
		print "B is a child class of A "
		super(B,self).fun1()
		#A.fun1()
		

obj=B()
obj.fu()
obj.fun1()
#obj.fun2()
