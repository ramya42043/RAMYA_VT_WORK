#!/usr/bin/python

from Tkinter import *

root = Tk()
for i in range(5):
	top = Toplevel(root,bd=4,bg="green")
	print top.wait_window()
top.mainloop()
