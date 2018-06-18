class A(object):
    pass
class B(A):
    pass

b = B()
print b.__class__.__name__
