#!/usr/bin/python
import re
string="Ip address of john's machine is 125.258.143.698 and lucky's machine is 583.254.125.789 .My machine's ip address was 587.256.235.125 but recently it is changed to 125.254.148.159 and another valid ip is 125.254.123.200 "
pattern=re.compile(" [1-5]{3}.[1-5]{3}.\d{3}.\d{3} ")
res = re.findall(pattern,string)
for i in res:
	print i
