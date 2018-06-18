#!/usr/bin/python
import MySQLdb

db = MySQLdb.connect("root","07Nov1994","sample")
cursor = db.cursor()
cusor.execute('insert into system_info (cdate,utime,fma) values ("a","b","c")')
db.commit()
db.close()
