def f1(arg):
	print "hi"
	def sum():
		print "hello"		
		arg() 
	return sum
@f1
def f2():
	print "f2 is called"

f2()