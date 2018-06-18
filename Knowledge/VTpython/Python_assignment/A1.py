#!/usr/bin/python
v1='0b1010'
v2='10'
v3='012'
v4='0xA'
print "Type is : ",type(v1),"V1 is : ",int(v1,2)
print "Type is : ",type(v2),"V2 is : ",int(v2,10)
print "Type is : ",type(v3),"V3 is : ",int(v3,8)
print "Type is : ",type(v4),"V4 is : ",int(v4,16)

v1='0b1010'
v2='10'
v3='012'
v4='0xA'
print "Type is : ",type(v1),"V1 is : ",long(v1,2)
print "Type is : ",type(v2),"V2 is : ",long(v2,10)
print "Type is : ",type(v3),"V3 is : ",long(v3,8)
print "Type is : ",type(v4),"V4 is : ",long(v4,16)

var=input("Please enter the value :\t")
res=float(var)
print "Float formate of given number is ",res

var1=input("Please enter the value :\t")
var2=input("Please enter the value :\t")
var3=input("Please enter the value :\t")
var1=str(var1)
var2=str(var2)
var3=str(var3)
res=var1+var2+var3
print "String formate is ",res

str1=raw_input("Please enter the string : ")
str1=list(str1)
print "Value is : ",str1[0],"ASCII is : ",ord(str1[0])
print "Value is : ",str1[1],"ASCII is : ",ord(str1[1])
print "Value is : ",str1[2],"ASCII is : ",ord(str1[2])
print "Value is : ",str1[3],"ASCII is : ",ord(str1[3])
print "Value is : ",str1[4],"ASCII is : ",ord(str1[4])
print
v1=input("please enter the octal number : ")
print "Binary formate of given number is ",bin(v1)
print "Decimal formate of given number is ",int(v1)
print "Octal formate of given number is ",oct(v1)
print "Hexadecimal formate of given number is ",hex(v1)
print
var=input("Please enter the value between 65 to 90 : ")
print "Given value is ",var,"and quivalant character is ",chr(var)
print
v1=input("please enter the number : ")
print "Binary formate of given number is ",bin(v1)
print "Decimal formate of given number is ",int(v1)
print "Octal formate of given number is ",oct(v1)
print "Hexadecimal formate of given number is ",hex(v1)
print
v1=input("please enter the binary number : ")
print "Binary formate of given number is ",bin(v1)
print "Decimal formate of given number is ",int(v1)
print "Octal formate of given number is ",oct(v1)
print "Hexadecimal formate of given number is ",hex(v1)
print
v1=input("please enter the octal number : ")
print "Binary formate of given number is ",bin(v1)
print "Decimal formate of given number is ",int(v1)
print "Octal formate of given number is ",oct(v1)
print "Hexadecimal formate of given number is ",hex(v1)
print
v1=input("please enter the hexdecimal number : ")
print "Binary formate of given number is ",bin(v1)
print "Decimal formate of given number is ",int(v1)
print "Octal formate of given number is ",oct(v1)
print "Hexadecimal formate of given number is ",hex(v1)
print
v1=input("please enter the decimal number : ")
print "Octal formate of given number is ",oct(v1)
v1=input("please enter the decimal number : ")
print "Hexadecimal formate of given number is ",hex(v1)
