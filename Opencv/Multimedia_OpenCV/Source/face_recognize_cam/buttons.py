#!/usr/bin/python
from Tkinter import *
import db
import train
import detect
import sys
import os
import tkMessageBox
root = Tk()
root.geometry("500x500")
menubar = Menu(root)
def add_person_cam():
	db.add_details(1)
	train.train_person()
def add_person_local():
	res = db.add_details(0)
	if res == 0:
		tkMessageBox.showinfo("error","invalid input image")
	else:
		train.train_person()
def detect_person_cam():
	if(os.path.isfile('recognizer/trainningData.yml') == True):
		res = detect.detect_person(1)
	else:
		tkMessageBox.showinfo("error","no trained data to detect image")
def detect_person_local():
	if(os.path.isfile('recognizer/trainningData.yml') == True):
		res= detect.detect_person(0)
		if res == 0:
			tkMessageBox.showinfo("error","invalidimage")
	else:
		tkMessageBox.showinfo("error","no trained data to detect image")
def close():
	root.destroy()
	sys.exit(1)
filemenu = Menu(menubar,tearoff=0)
filemenu.add_command(label="camera",command=add_person_cam)
filemenu.add_command(label="local",command=add_person_local)
menubar.add_cascade(label="Add person", menu=filemenu)
editmenu = Menu(menubar,tearoff=0)
editmenu.add_command(label="camera",command=detect_person_cam)
editmenu.add_command(label="local",command=detect_person_local)
menubar.add_cascade(label="Detect person", menu=editmenu)
close_button = Button(root,text="close",command=close)
close_button.pack(side="bottom")
root.config(menu=menubar)
root.mainloop()







































"""

gCamera=0
gbuttons=0
def enter_db():
	global gCamera
	db.add_details(gCamera)
	train.train_person()
def layer():
	global gbuttons
	if gbuttons == 1:
		return
	b1 = Button(root,text="add",command=enter_db)
	b1.pack()
	b2 = Button(root,text="detect",command=detect_layer)
	b2.pack()
	gbuttons=1
def detect_layer():
	global gCamera
	detect.detect_person(gCamera)
	
def cam_function():
	global gCamera
	gCamera = 1
	layer()
def local_function():
	global gCamera
	gCamera = 0
	layer()
def close():
	root.destroy()
	sys.exit(1)
if __name__ == "__main__":
	global flag
	flag=1
	b = Button(root,text="Cam",command=cam_function)
	b.pack()
	b4 = Button(root,text="local",command=local_function)
	b4.pack()
	b5 = Button(root,text="close",command=close)
	b5.pack(side="bottom")
	root.mainloop()
"""
