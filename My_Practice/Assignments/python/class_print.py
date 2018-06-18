#!/usr/bin/python
class iostring():
	def __init__(self):
		self.s = ''
	def get_String(self):
		self.s = raw_input("Enter a string")
	def print_String(self):
		print self.s.upper()
s = iostring()
s.get_String()
s.print_String()
