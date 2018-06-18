import MySQLdb, subprocess, re, sys, time, telnetlib

def tel_connect():
	tn = telnetlib.Telnet("linuxzoo.net")
	tn.read_until("login: ")
	tn.write("root"+"\n")
	tn.read_until("Password: ")
	tn.write("secure"+"\n")
	tn.read_until("# ")

	return tn

def get_date():
	tn = tel_connect()
	tn.write("date"+"\n")
	return tn.read_until("# ")


def get_ut_fa():
	tn = tel_connect()
	tn.write("uptime"+"\n")
	u_out = tn.read_until("# ")
	mat = re.search(r"up\s(.+?),.+load\saverage:\s(.+?),", u_out)
	utime = mat.group(1)
	fm_avg = mat.group(2)

	return utime, fm_avg

def insert_to_db():
	cur_date = get_date()
	for line in cur_date.split("\r\n"):
		mat = re.search(r"\w{3}\s+\d{1,2}\s+\w{3}\s+\d{2}:\d{2}:\d{2}\s+\w+\s\d{4}", line)
		if mat:
			curr_date = mat.group()
			break
		
	utime, fm_avg = get_ut_fa()
	conn = MySQLdb.connect(user="root", passwd="admin@123", db="students")
	c = conn.cursor()
	c.execute('insert into system_info (cdate, utime, fma) values(%s, %s, %s)', (curr_date, utime, fm_avg))
	conn.commit()
	conn.close()

if __name__ == "__main__":
	insert_to_db()

