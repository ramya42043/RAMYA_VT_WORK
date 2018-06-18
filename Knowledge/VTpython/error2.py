try:
		b =input("enter the number ")
		raise TypeError(b)
except TypeError as b :
		b=int(b)
		print b+100 , "your total score"
