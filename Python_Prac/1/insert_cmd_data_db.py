import MySQLdb, subprocess, re, sys, time

def get_date():
	return time.ctime()

def get_ut_fa():
	op = subprocess.Popen(['uptime'], stdout=subprocess.PIPE)
	#print op.communicate()
	u_out, u_err = op.communicate()
	if u_err:
		print "Error in command execution"
		sys.exit(100)

	#17:48:12 up 31 min,  1 user,  load average: 0.13, 0.19, 0.25

	mat = re.search(r"up\s(.+?),.+load\saverage:\s(.+?),", u_out)
	utime = mat.group(1)
	fm_avg = mat.group(2)

	return utime, fm_avg

def insert_to_db():
	curr_date = get_date()
	utime, fm_avg = get_ut_fa()
	conn = MySQLdb.connect(host="192.168.2.105",user="root", passwd="deepu2305", db="students")
	c = conn.cursor()
	c.execute('insert into system_info (cdate, utime, fma) values(%s, %s, %s)', (curr_date, utime, fm_avg))
	conn.commit()
	conn.close()

if __name__ == "__main__":
	insert_to_db()

