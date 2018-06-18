#!/usr/bin/python
from ctypes import *

#path=raw_input("enter file path:")
path="song.mp3"
cfun=CDLL("./test_pitch_tempo.so")
tempo=cfun.start(path)

if tempo==1:
	print "Pass"
else:
	print "Fail"
