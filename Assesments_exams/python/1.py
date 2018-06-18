#!/usr/bin/python
import re
string="I used to have 4563-987-1234 as my phone number ,but now I have changed it to 567-345-2318 .as it numerically not suitable with my lucky number I have changed it to 589-574-1258 My grandfather used to have 5874-587-254169 as his phone number but now a days phone numbers with these many digits are invalid"
pattern=re.compile(" \d{3}-\d{3}-\d{4} ")
res = re.findall(pattern,string)
for i in res:
	print i
