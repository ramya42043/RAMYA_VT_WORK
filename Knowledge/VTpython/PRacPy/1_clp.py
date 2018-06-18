#!/usr/bin/python

class parentclass(object):

	def parentmember(self):
		print "parent member is called"

class childclass(parentclass):
		
	def childmember(self):
		print "child member is called"
	def callparentmembers(self):
		self.parentmember()
	def callparentmembersusingsuper(self):
		print "super class is used"
                super(childclass,self).parentmember()


obj=childclass()
obj.childmember()
obj.callparentmembers()
obj.parentmember()
obj.callparentmembersusingsuper()

