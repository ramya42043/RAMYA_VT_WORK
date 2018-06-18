#!/usr/bin/python

class A:

	y=10	

	def __init__(self,y):
		self.y=y


	def add(self,x):
		print "hello we are in parent class"
		print x
		print self.y
		print A.y	

obj=A(2)
obj.add(88)
