import ast
def ConfigDict(d):
	f=open(d,"r")
	d=f.readline()
	d=ast.literal_eval(d)
	return d
	
