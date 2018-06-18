#!/usr/bin/python
import os,shutil
#sourcepath ='/home/chaturah/Desktop/source/'
#destinationpath = '/home/chaturah/Desktop/Destination/'

destinationpath ='/home/chaturah/Desktop/source/'
sourcepath = '/home/chaturah/Desktop/Destination/'

source = os.listdir(sourcepath)
for files in source:
    if files.endswith('.cpp') or files.endswith( '.c') or files.endswith('.py') or files.endswith( '.pl') or files.endswith( '.sh'):
        #shutil.move(os.path.join(sourcepath,files), os.path.join(destinationpath))
        shutil.move(os.path.join(sourcepath,files), os.path.join(destinationpath))
print"***END OF PROGRAM***"
