import imaplib
import datetime
CONN = imaplib.IMAP4_SSL("imap.mail.yahoo.com")
CONN.login("ashashishpoojala@yahoo.com", "ashoksivakumar")
status,messages = CONN.select("INBOX")
print messages
date = (datetime.date.today() - datetime.timedelta(1)).strftime("%d-%b-%Y")
print date
(typ,data1)=CONN.uid('search', '(UNSEEN)', '(HEADER Subject "Jenkins")','(SENTSINCE {0})'.format(date))
for i in data1:
	if i:
		#import subprocess
		import os
		import turtle
		turtle.write("build error",align='center',font=('Arial',50,'normal'))
		store = turtle.Screen()
		store.bgcolor("violet")
		os.system('echo "build error mail came,please check" | festival --tts')
		#subprocess.call(['speech-dispatcher'])
		#subprocess.call(['spd-say','"build error mail"'])
		#from espeak import espeak
		#espeak.synth("build error mail came")
		raw_input("enter")

