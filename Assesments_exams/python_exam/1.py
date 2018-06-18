#!/usr/bin/python 
import sys
class Account:
		
	def __init__(self,name,accnum,balance):
		self.name = name
		self.accnum = accnum
		self.balance = balance
	
	def tansfer_to_Account(self):
		accnum = input("enter account number to transfer")
		amount = input("enter amount")
		if self.balance < amount:
			print "amount is not suuficient"
			sys.exit(1)
		self.balance = self.balance-amount
		
	def Deposit(self):
		amount = input("enter amount to deposit")
		self.balance = self.balance+amount
	
	def withdraw(self):
		amount = input("enter amount to withdraw")
		if self.balance < amount:
			print "amount is not suuficient"
			sys.exit(1)
		self.balance = self.balance-amount

	def display_balance(self):
		print "current Balance is:", self.balance

emp1=Account("Ramya",1234,5000)
emp1.tansfer_to_Account()
emp1.display_balance()
emp1.Deposit()
emp1.display_balance()
emp1.withdraw()
emp1.display_balance()
