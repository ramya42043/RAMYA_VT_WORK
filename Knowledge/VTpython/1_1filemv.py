import os
import shutil
source = os.listdir('/Users/user/Desktop/')
destination = '/Users/user/Desktop/Archiev'
for files in source:
    print files
    if files.endswith('.odt'):
        print files
        shutil.move(files, destination)
        print "files"

             
