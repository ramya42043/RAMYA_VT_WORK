import os
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
        cvInstance.showImageWithName(faceNp)
        cvInstance.waitWindow(10)
    return np.array(IDs),faces
def train_person():
	IDs,faces=getImagesWithID(path)
	cvInstance=OPENCV_Wrapper()
	cvInstance.recogniserLBPHFaceRecognizer()
	cvInstance.recogniserTrain(faces,IDs)
	cvInstance.recogniserWrite('recognizer/trainningData.yml')
	cvInstance.destroyAllopenWindows()

