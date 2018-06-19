import cv2
import numpy as np
import sqlite3
import time
from Tkinter import *
from wrapper import *
def local_browse():
	from tkFileDialog import askopenfilename
	Tk().withdraw()
	browse = askopenfilename()
	return browse

def insertOrUpdate(Id,Name,Age,Gen,CR):
    conn=sqlite3.connect("FaceBase.db")
    cmd="SELECT * FROM People WHERE ID="+str(Id)
    cursor=conn.execute(cmd)
    isRecordExist=0
    for row in cursor:
        isRecordExist=1
    if(isRecordExist==1):
        cmd="UPDATE People SET Name="+str(Name)+"WHERE ID="+str(Id)
        cmd2="UPDATE People SET Age="+str(Age)+"WHERE ID="+str(Id)
        cmd3="UPDATE People SET Gender="+str(Gen)+"WHERE ID="+str(Id)
        cmd4="UPDATE People SET CR="+str(CR)+"WHERE ID="+str(Id)
    else:
        cmd="INSERT INTO People(ID,Name,Age,Gender,CR) Values("+str(Id)+","+str(Name)+","+str(Age)+","+str(Gen)+","+str(CR)+")"
        cmd2=""
        cmd3=""
        cmd4=""
    conn.execute(cmd)
    conn.execute(cmd2)
    conn.execute(cmd3)
    conn.execute(cmd4)
    conn.commit()
    conn.close()
def add_details(arg):
	#faceDetect=cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
	cvInstance=OPENCV_Wrapper()
	"""
	a.read_image("1.jpg")
	a.show_image()
	a.waitWindow(2000)
	"""
	cvInstance.readClassifier('haarcascade_frontalface_default.xml')
	if arg == 1:
		#cam=cv2.VideoCapture(0)
		cvInstance.cameraSelect()
	elif arg == 0:
		browse = local_browse()	
	Id=raw_input('Enter User Id')
	name=raw_input('Enter User Name')
	age=raw_input('Enter User Age')
	gen=raw_input('Enter User Gender')
	cr=raw_input('Enter User Criminal Records')
	insertOrUpdate(Id,name,age,gen,cr)
	sampleNum=0
	while(True):
		if arg == 1:
			#ret,img=cam.read()
			cvInstance.cameraRead()
			time.sleep(1)
		if arg == 0:
			#img=cv2.imread(browse)
			cvInstance.readImage(browse)
		#gray=cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
		cvInstance.grayImage()
		#faces=faceDetect.detectMultiScale(gray,1.3,5)
		faces=cvInstance.detectMultiScale()
		if len(faces) == 0 and arg ==0:
			return 0
		for(x,y,w,h) in faces:
			sampleNum=sampleNum+1;
			#cv2.imwrite("dataSet/User."+str(Id)+"."+str(sampleNum)+".jpg",gray[y:y+h,x:x+w])
			cvInstance.imageSave("dataSet/User."+str(Id)+"."+str(sampleNum)+".jpg",x,y,w,h)
			#cv2.rectangle(img,(x,y),(x+w,y+h),(0,255,0),2)
			cvInstance.drawRectangle(x,y,w,h)
			#cv2.waitKey(100)
			cvInstance.waitWindow(100)
		#cv2.imshow("Face",img)
		cvInstance.showImage()
		#cv2.waitKey(1)
		cvInstance.waitWindow(1)
		if(sampleNum>20):
			break;
	if arg ==1:
		#cam.release()
		cvInstance.cameraRelease()
	#cv2.destroyAllWindows()
	cvInstance.destroyAllopenWindows()
