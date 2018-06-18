#!/usr/bin/python
class String():
	empcount=0
	def getString(self):
		self.mystr=raw_input("Please enter the string : ")
		String.empcount+=1
	def printString(self):
		print"Given Data is ",self.mystr.upper()
		print"Count is ",self.empcount
		print"Count is ",String.empcount
		
obj=String()
obj.getString()
obj.printString()
