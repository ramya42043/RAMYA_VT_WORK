import cv2
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
	#faceDetect=cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
	cvInstance=OPENCV_Wrapper()
	cvInstance.readClassifier('haarcascade_frontalface_default.xml')
	if arg == 1:
		#cam=cv2.VideoCapture(0)
		cvInstance.cameraSelect()
	elif arg == 0:
		browse = local_browse()	
	#rec=cv2.face.LBPHFaceRecognizer_create()
	cvInstance.recogniserLBPHFaceRecognizer()	
	#rec.read("recognizer/trainningData.yml")
	cvInstance.recogniserLoad("recognizer/trainningData.yml")
	while(True):
		if arg == 1:
			#ret,img=cam.read()
			cvInstance.cameraRead()
		if arg == 0:
			#img=cv2.imread(browse)
			cvInstance.readImage(browse)
		#gray=cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
		cvInstance.grayImage()
		#faces=faceDetect.detectMultiScale(gray,1.1,10,minSize=(30,30))
		faces=cvInstance.detectMultiScale()
		if len(faces) == 0 and arg ==0:
			return 0
		for(x,y,w,h) in faces:
			#cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
			cvInstance.drawRectangle(x,y,w,h)
			#face = gray[y:y + h, x:x + w]
			#face_resize = cv2.resize(face, (width, height))
			cvInstance.resizeImage(x,y,w,h,width,height)
			#ids,conf = rec.predict(face_resize)
			ids,conf = cvInstance.recogniserPredict()
			print ids,conf
			if conf < 70:
				profile=getProfile(ids)
				if(profile!=None):
					#cv2.putText(img,"Name : "+str(profile[1]),(x,y+h+20),font,fontScale,(0,255,0))
					cvInstance.putTextOnImage("Name : "+str(profile[1]),x,y,w,h,20,(0,255,0))
					#cv2.putText(img,"Age : "+str(profile[2]),(x,y+h+45),font,fontScale,(0,255,0))
					cvInstance.putTextOnImage("Age : "+str(profile[2]),x,y,w,h,45,(0,255,0))
					#cv2.putText(img,"Gender : "+str(profile[3]),(x,y+h+70),font,fontScale,(0,255,0))
					cvInstance.putTextOnImage("Gender : "+str(profile[3]),x,y,w,h,70,(0,255,0))
					#cv2.putText(img,"Criminal Records : "+str(profile[4]),(x,y+h+95),font,fontScale,(0,0,255))
					cvInstance.putTextOnImage("Criminal Records : "+str(profile[4]),x,y,w,h,95,(0,0,255))
			else:
				#cv2.putText(img,"Name :Unknown",(x,y+h+20),font,fontScale,(0,255,0));
				cvInstance.putTextOnImage("Name :Unknown",x,y,w,h,20,(0,255,0))
			#cv2.imshow("Face",img)
			cvInstance.showImage()
		#if(cv2.waitKey(1)==ord('q')):
		if(cvInstance.waitWindow(1)==ord('q')):
		    break;
	if arg == 1:
		#cam.release()
		cvInstance.cameraRelease()
	#cv2.destroyAllWindows()
	cvInstance.destroyAllopenWindows()

