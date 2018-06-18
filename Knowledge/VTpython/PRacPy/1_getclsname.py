
class Parent(object):
    def type(self):
         print Parent.__name__
class Child(Parent):
	def getclsname(self):
		# super(Child,self).type()
		Parent.type(self)

p = Child()
p.getclsname()
