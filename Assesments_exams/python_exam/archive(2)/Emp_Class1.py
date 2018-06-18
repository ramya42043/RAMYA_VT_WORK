#!/usr/bin/python 

class Employee:
	'This is a Sample class program!'
	emp_count=0
	def __init__(self,name,salary):
		self.name=name
		self.salary=salary
		Employee.emp_count+=1
	
	def display_count(self):
		print"Employee Count through class is {}".format(Employee.emp_count)
		print"Employee Count through self is ",self.emp_count

	def display_employee(self):
		print"Name :{} and Salary :{}".format(self.name,self.salary)

print "Employee.__doc__ :",Employee.__doc__
print "Employee.__name__ :",Employee.__name__
print "Employee.__module__ :",Employee.__module__
print "Employee.__bases__ :",Employee.__bases__
print "Employee.__dict__ :",Employee.__dict__

