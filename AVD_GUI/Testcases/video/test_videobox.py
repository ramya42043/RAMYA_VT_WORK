#!/usr/bin/python
from ctypes import *
import ctypes
cfun=CDLL("./videobox.so")
foo=cfun.start()
print foo
#print ctypes.c_char_p(foo).value
