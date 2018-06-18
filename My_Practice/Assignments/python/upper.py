from string import *

lines = []
print "Enter sequence of lines: "

while True:
	line = raw_input("> ")
	if not line:
		break
	print line.upper()

#print lines
