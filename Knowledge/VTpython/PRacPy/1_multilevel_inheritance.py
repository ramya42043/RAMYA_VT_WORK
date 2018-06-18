#!/usr/bin/python
#Sample Program of Multilevel Inheritance

class Animal(object):  
	def __init__(self,name):
		self.name=name
	def getname(self):  
		print self.name
	def printme(self):
		print "hello"  
class Dog(Animal): 
	def __init__(self,name,sound):
		super(Dog,self).__init__(name)
		self.sound=sound 
	def getsound(self):  
		print self.sound
class BabyDog(Dog):
	def __init__(self,name,sound,status):
		super(BabyDog,self).__init__(name,sound)
		self.status=status  
	def getstatus(self):  
	        print self.status

	def getallinfo(self):
		super(BabyDog,self).getname()
		super(BabyDog,self).getsound()
		self.getstatus()

d=BabyDog("Dog","Barking","weeping")  
#d=BabyDog()  
d.printme()
d.getname()
d.getsound()  
d.getstatus()
d.getallinfo()
