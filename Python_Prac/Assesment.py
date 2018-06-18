import  telnetlib

def tel_connect():
	tn = telnetlib.Telnet("linuxzoo.net")
	tn.read_until("login: ")
	tn.write("root"+"\n")
	tn.read_until("Password: ")
	tn.write("secure"+"\n")
	tn.read_until("# ")

	return tn
def get_ut_fa():
	tn = tel_connect()
	tn.write("uptime"+"\n")
	u_out = tn.read_until("# ")
	return u_out

if __name__ == "__main__":
	print get_ut_fa()
