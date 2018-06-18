#!/usr/bin/python
from Tkinter import *
l = []
root = Tk()
for i in range(5):
	top = Toplevel(root,bd=3)
	l.append(top)
print l
root.iconify()

if(root.iconify() == None):
	for i in range(len(l)):
		l[i].iconify()
else:
	print "not minimised"

root.mainloop()

