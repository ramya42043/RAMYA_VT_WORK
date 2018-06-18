#!/usr/bin/python

from Tkinter import *
import thread
import time
row =2
colum = 2

list1 = [0,0,0,0]
def fun(i):
	global list1
	if list1[i]==0:
		return 0
def update(i,j):
	global list1
	list1[i]=j

def mine(a):
	print "A value",a
	global list1
	k = 0
	for i in range(row):
			for j in range(colum):
				if k == a:
					update(k,1)
					Root = Tk()
					print "before close",Root.winfo_exists()
					width=((Root.winfo_screenwidth()-100)/row)
					height=((Root.winfo_screenheight()-100)/colum)
					#b = Button(Root,text="close",command=Root.destroy)
					#b.pack()
					print "k,a",k,a,width,height,j*(width+100),i*(height+100)
					Root.geometry('{}x{}+{}+{}'.format(width,height,j*(width+100),i*(height+100)))
					#Root.update()
					Root.mainloop()
					update(k,0)
					break
				k += 1
while True:		
	for i in range(4):
		if fun(i) == 0:
			mine,(i,))
	#raw_input("enter")
	time.sleep(5)
