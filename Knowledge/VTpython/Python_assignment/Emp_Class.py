#!/usr/bin/python 

class Employee:
	
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

emp1=Employee("Rahul",10000)
emp2=Employee("Aman",20000)
emp1.display_employee()
emp2.display_employee()
emp1.display_count()
print"Total Employee Count is {}".format(Employee.emp_count)

