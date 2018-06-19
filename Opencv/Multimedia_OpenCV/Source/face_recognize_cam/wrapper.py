import cv2
class OPENCV_Wrapper():
	font=cv2.FONT_HERSHEY_COMPLEX
	fontScale=0.4
	fontclor=(1,0,1)
	(width,height)=(130, 100)
	def __init__(self):
		print "good"
		self.CV=cv2
		
	def cameraSelect(self):
		self.camera=self.CV.VideoCapture(0)
		
	def cameraRead(self):
		self.success,self.image=self.camera.read()
		
	def readImage(self,image_name):
		self.image = self.CV.imread(image_name,1)
		
	def showImage(self,windowName="Image Window"):
		self.CV.imshow(windowName,self.image)
		
	def showImageWithName(self,image,windowName="Image Window"):
		self.CV.imshow(windowName,image)
		
	def grayImage(self):
		self.gray=cv2.cvtColor(self.image,cv2.COLOR_BGR2GRAY)
		
	def showGray(self):
		self.CV.imshow("good",self.gray)
		
	def imageSave(self,name,x,y,w,h):
		self.CV.imwrite(name,self.gray[y:y+h,x:x+w])
		
	def drawRectangle(self,x,y,w,h):
		self.CV.rectangle(self.image,(x,y),(x+w,y+h),(0,255,0),2)
		
	def waitWindow(self,arg):
		return self.CV.waitKey(arg)
		
	def cameraRelease(self):
		self.camera.release()
		
	def recogniserLBPHFaceRecognizer(self):
		self.recogniser=self.CV.face.LBPHFaceRecognizer_create()
		
	def recogniserTrain(self,faces,labels):
		self.recogniser.train(faces,labels)
		
	def recogniserWrite(self,name):
		self.recogniser.write(name)
		
	def destroyAllopenWindows(self):
		self.CV.destroyAllWindows()
		
	def resizeImage(self,x,y,w,h,width,height):
		self.faceResize = cv2.resize(self.gray[y:y + h, x:x + w], (width, height))
		
	def recogniserLoad(self,name):
		self.recogniser.read(name)
		
	def recogniserPredict(self):
		ids,predict=self.recogniser.predict(self.faceResize)
		return ids,predict
		
	def putTextOnImage(self,name,x,y,w,h,step,color):
		self.CV.putText(self.image,name,(x,y+h+step),self.font,self.fontScale,color);
		
	def readClassifier(self,name):
		self.classifier=self.CV.CascadeClassifier(name)
		
	def detectMultiScale(self):
		faces=self.classifier.detectMultiScale(self.gray,1.3,5)
		return faces
