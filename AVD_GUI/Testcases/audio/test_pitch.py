#!/usr/bin/python
from ctypes import *

#path=raw_input("enter file path:")
path="song.mp3"
cfun=CDLL("./test_pitch.so")
pitch=cfun.start(path)
#print bright
if pitch==1:
	print "Pass"
else:
	print "Fail"
