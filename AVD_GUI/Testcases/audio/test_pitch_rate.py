#!/usr/bin/python
from ctypes import *

#path=raw_input("enter file path:")
path="song.mp3"
cfun=CDLL("./test_pitch_rate.so")
rate=cfun.start(path)

if rate==1:
	print "Pass"
else:
	print "Fail"
