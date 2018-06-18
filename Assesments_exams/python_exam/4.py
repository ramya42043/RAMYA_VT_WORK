#!/usr/bin/python 
import sys
class FileOperation:
		
	def __init__(self,string):
		self.string = string
	
	def read_n_lines(self,lines):
		self.lines=lines
		print "".join(self.string[:lines])
	
	def read_lines_range(self,line1,line2):
		self.line1 = line1
		self.line2 = line2
		print "".join(self.string[line1-1:line2-1])
	
fp = open("file1.txt","r")
buffer = fp.readlines()
obj=FileOperation(buffer)
obj.read_n_lines(3)
obj.read_lines_range(2,5)
obj.read_n_lines(3)
