#!/usr/bin/python
import threading
def add(a,b):
	f = open('file.txt','w')
	f.write("addition of two numbers%d\n"%(a+b))
	f.close()
def sub(a,b):
	f = open('file.txt','a')
	f.write("subraction of two numbers%d\n"%(a-b))
	f.close()
thr1 = threading.Thread(target=add,args =(2,3))
thr2 = threading.Thread(target=sub,args = (10,2))
thr1.start()
thr2.start()
thr1.join()
thr2.join()
