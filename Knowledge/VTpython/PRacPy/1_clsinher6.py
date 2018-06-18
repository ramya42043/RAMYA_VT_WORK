#!/usr/bin/python

class A(object) :

	def __init__(self):
		self.x=x
		self.y=y

	def add(self):
		print "im in add"

class B(A) :
	def __init__(self):
	  print "i'm in child"

	def add(self):
		super(B,self).add()
		print "im in child add"

obj= B()	

obj.add()
		
