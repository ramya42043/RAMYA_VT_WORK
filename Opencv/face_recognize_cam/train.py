import os
import cv2
import numpy as np
from PIL import Image
from wrapper import *

path='dataSet'


def getImagesWithID(path):

    imagepaths=[os.path.join(path,f) for f in os.listdir(path)]
    faces=[]
    IDs=[]
    cvInstance=OPENCV_Wrapper()
    for imagepath in imagepaths:
    	faceImg=Image.open(imagepath).convert('L')
        faceNp=np.array(faceImg,'uint8')
        ID= int((os.path.split(imagepath)[-1].split('.')[1]).split('"')[1])
        faces.append(faceNp)
        IDs.append(ID)
        #cv2.imshow("training",faceNp)
        cvInstance.showImageWithName(faceNp)
        #cv.waitKey(10)
        cvInstance.waitWindow(10)
    return np.array(IDs),faces
def train_person():
	IDs,faces=getImagesWithID(path)
	cvInstance=OPENCV_Wrapper()
	#recognizer=cv2.face.LBPHFaceRecognizer_create()
	cvInstance.recogniserLBPHFaceRecognizer()
	#recognizer.train(faces,IDs)
	cvInstance.recogniserTrain(faces,IDs)
	#recognizer.write('recognizer/trainningData.yml')
	cvInstance.recogniserWrite('recognizer/trainningData.yml')
	#cv2.destroyAllWindows()
	cvInstance.destroyAllopenWindows()

