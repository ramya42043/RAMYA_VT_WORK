#!/usr/bin/python

try : 

	print 5/1
	raise ZeroDivisionError(55555)

except ZeroDivisionError as e:
	
	print e,"zero division error"

else :

	print "error not found"

finally :

	print "program excuted"

