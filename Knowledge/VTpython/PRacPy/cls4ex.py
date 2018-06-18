#!/usr/bin/python

class A:

	count = 5
	
	def getcount(self):
		print A.count
		print self.count



obj=A()
obj.getcount()
