#!/usr/bin/python

def print0to6skip3and6():
	
	for number in range(0,7):
		if 3 == number or 6 == number:
			continue
		else:
			print number


print0to6skip3and6()
