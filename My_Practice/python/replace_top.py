#!/usr/bin/python
from Tkinter import *
import gc
gc.disable()
root = Tk()
root["bg"]="pink"
top = Toplevel(root,bd=4)
if True: 
	if top.winfo_exists == 0:
		print "loop"
		top = Toplevel(root,bd=4)
	else:
		pass
root.mainloop()
