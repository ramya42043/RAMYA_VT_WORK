"""
--------------------------------------------------
 mathhoang (mathhoang.blogspot.com)
--------------------------------------------------
   This example is to demonstrate the inheritance in Python.
   In this example, we have one parent class and 2 children classes which inherit
   their parent classe (particularly, it is person in our case)

   Super class: person has first and last name and a method called "getName"
   child class 1: Employee does not only have has first and last name, but also
                  has staff number
   child class 2: Boss: has first, last name and title

                 person
                   |
                   |
           +-------------+
           |             |
        Employee       Boss
"""

#----- Parent class: person --------
class person(object):
    def __init__(self,first,last):
        self.firstName = first
        self.lastName = last

    def getName(self):
	print "person getName function"
        return self.firstName + " " + self.lastName
	#return "5"
"""
#----- child class: Employee inherited from person --------
class Employee(person):
    def __init__(self,first,last,staffNum):
        person.__init__(self,first,last)
        self.staffNum = staffNum

    def getEmployee(self):
        return self.getName() + ": " + self.staffNum
"""
#----- child class: Employee inherited from person --------
class Boss(person):
    def __init__(self,first,last,title):
        #person.__init__(self,first,last)
	super(Boss,self).__init__(first,last)
        self.title = title

    def getBoss(self):
        return self.getName() + ": Employee ID: " + self.title




obj=Boss("meena","paleti","emp1")
print obj.getBoss()
print obj.getName()

"""

#----- instantiate class --------    
#person_1 = person("Math", "Hoang")
#Employee_1 = Employee("Math", "Hoang", "12344")
Employee_2 = Employee("Blog", "spot", "43211")
Boss_ = Boss("Mathhoang", "Blogspot.com", "CEO")

#------ print out information ------
#print(person_1.getName())
#print(Employee_1.getEmployee())
print(Employee_2.getEmployee())
print(Boss_.getBoss())
"""
