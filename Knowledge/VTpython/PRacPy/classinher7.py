class a:

	def __init__(self,x,y):
		self.x=x
		self.y=y
	def __add__(self):
		res = self.x + self.y
		print res
		res1=str(self.x) + str(self.y)
		print res1

obj=a(2,3)
obj.__add__()

#obj.ad()

