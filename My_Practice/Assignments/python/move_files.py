import os
import shutil
sourcepath ='/home/dasinram/Desktop/'
source = os.listdir(sourcepath)
destinationpath = '/home/dasinram/Desktop/'
for files in source:
    if files.endswith('.py'):
        shutil.move(os.path.join(sourcepath,'4notification'), os.path.join(destinationpath,'Archive'))
