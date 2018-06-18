import telnetlib
import re


tn = telnetlib.Telnet("linuxzoo.net")
tn.read_until("login: ")
tn.write("root"+"\n")
tn.read_until("Password: ")
tn.write("secure"+"\n")
tn.read_until("# ")
tn.write("who|awk '{print $1}'|sort -u|wc -l"+"\n")
op = tn.read_until("# ")
nu = ""
for line in op.split("\r\n"):
	mat = re.match(r"(\d+)", line)
	if mat:
		nu = mat.group(1)
print "Number of users logged in:", nu 

