#!/usr/bin/python

class A:

	def __init__(self,x,y):
		self.x=x
		self.y=y
	def getxvalue(self):
		print self.x
	def getyvalue(self):
		print self.y

obj=A(5,2)
obj.getxvalue()


