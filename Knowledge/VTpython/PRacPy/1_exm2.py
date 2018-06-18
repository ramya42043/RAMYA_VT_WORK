#!/usr/bin/python

class A(object):

	def __init__(self,x,y):
		self.x=x
		self.y=y
	
	def add(self):
		print self.x+self.y

class B(object):
	
	def __init__(self,x,y):
		self.x=x
		self.y=y
	def mul(self):
		print self.x * self.y

class C(object):
	
	def __init__(self,x,y):
		self.x=x
		self.y=y
	def sub(self):
		print self.x - self.y

class D(A,B,C):
	
	def __init__(self,x,y):
		super(D,self).__init__(x,y)
		#A.__init__(self,x,y)
		#B.__init__(self,x,y)
		#C.__init__(self,x,y)
		
	#def add(self):
		#print "self.x+self.y"

	def getadd(self):
		self.add()
		#super(D,self).add()

	def getmul(self):
		self.mul()
		#super(D,self).mul()

	def getsub(self):
		self.sub()
		#super(D,self).sub()

obj=D(5,5)
obj.getadd()
obj.getmul()
obj.getsub()
