#!/usr/bin/python
class base(object):
	def __init__(self,str):
		self.str=str
	def display_str(self):
		print self.str
	
class derive(base):
	def __init__(self,str,name):
		super(derive,self).__init__(str)			
		self.name=name
	def display_name(self):
		print self.name
	
obj=derive("Hello", "Ramya")
obj.display_str()
obj.display_name()
