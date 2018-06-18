#!/usr/bin/python

def rotate_left3(arr):
	
	newarr=arr[1:]+arr[:1]
	return newarr

lis=input("enter integers the list format")
print rotate_left3(lis)
