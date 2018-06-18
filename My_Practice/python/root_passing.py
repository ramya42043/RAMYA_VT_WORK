#!/usr/bin/python
from Tkinter import *
import time
l1 = [0,0,0,0]
def f1(r,index):
	c1 = Toplevel(r)
	l1[index] = c1
def check():
	for i in range(len(l1)):
		if l1[i] == 0:
			return 0,i
		elif l1[i].winfo_exists() == 0:
			l1[i] =0
			return 0,i
	return 1,0
					
def main():
	root = Tk()
	while True:
		s,i = check()
		print "ramya",s
		if s == 0:
			print "if"
			f1(root,i)
			time.sleep(1)
			print "after if"
		elif s ==1:
			time.sleep(3)
	root.mainloop()
while True:
	main()
	#raw_input("enter")

