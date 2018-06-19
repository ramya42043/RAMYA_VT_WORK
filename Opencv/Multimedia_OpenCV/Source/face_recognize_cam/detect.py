import numpy as np
import sqlite3
from wrapper import *
from Tkinter import *
(width,height)=(130, 100)
def local_browse():
	from tkFileDialog import askopenfilename
	Tk().withdraw()
	browse = askopenfilename()
	return browse
def getProfile(ids):
	conn=sqlite3.connect("FaceBase.db")
	cmd="SELECT * FROM People WHERE ID=\""+str(ids)+"\""
	cursor=conn.execute(cmd)
	profile=None
	for row in cursor:
		profile=row
	conn.close()
	return profile
def detect_person(arg):
	cvInstance=OPENCV_Wrapper()
	cvInstance.readClassifier('haarcascade_frontalface_default.xml')
	if arg == 1:
		cvInstance.cameraSelect()
	elif arg == 0:
		browse = local_browse()
	cvInstance.recogniserLBPHFaceRecognizer()
	cvInstance.recogniserLoad("recognizer/trainningData.yml")
	while(True):
		if arg == 1:
			cvInstance.cameraRead()
		if arg == 0:
			cvInstance.readImage(browse)
		cvInstance.grayImage()
		faces=cvInstance.detectMultiScale()
		if len(faces) == 0 and arg ==0:
			return 0
		for(x,y,w,h) in faces:
			cvInstance.drawRectangle(x,y,w,h)
			cvInstance.resizeImage(x,y,w,h,width,height)
			ids,conf = cvInstance.recogniserPredict()
			print ids,conf
			if conf < 70:
				profile=getProfile(ids)
				if(profile!=None):
					cvInstance.putTextOnImage("Name : "+str(profile[1]),x,y,w,h,20,(0,255,0))
					cvInstance.putTextOnImage("Age : "+str(profile[2]),x,y,w,h,45,(0,255,0))
					cvInstance.putTextOnImage("Gender : "+str(profile[3]),x,y,w,h,70,(0,255,0))
					cvInstance.putTextOnImage("Criminal Records : "+str(profile[4]),x,y,w,h,95,(0,0,255))
			else:
				cvInstance.putTextOnImage("Name :Unknown",x,y,w,h,20,(0,255,0))
			cvInstance.showImage()
		if(cvInstance.waitWindow(1)==ord('q')):
		    break;
	if arg == 1:
		cvInstance.cameraRelease()
	cvInstance.destroyAllopenWindows()

