#!/usr/bin/python

def matched(str):
	ope = []
	clo = []
	print type(clo)
	for i in range(0,len(str)):
		l = str[i]
		if l == "{":
        		ope = ope + ["{"]
   		else:
        		if l == "}":
            			clo = clo  + ["}"]
		        else:
				return(ope, clo)
	if len(ope)==len(clo):
    		return True

	else:
   		 return False

string=raw_input("Enter the string\n ")
result=matched(string)
print result
