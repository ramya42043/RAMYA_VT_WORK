#!/usr/bin/pyhton
""" 
child class inherits method from parent class wich takes arguments
"""

class parent:
	__count = 10
	def add(self,x,y):
		print x+y
	def __cnt(self):
		print "dwqhfkl"

class child(parent):
	
	print "Inherit parent class "



obj1=parent()
#print obj1.__count,"obj"
print obj1._parent__count
obj=child()

obj.add(5,5)
