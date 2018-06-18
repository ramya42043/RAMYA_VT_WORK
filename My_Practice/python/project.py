import imaplib
import datetime
import  email
CONN = imaplib.IMAP4_SSL("imap.mail.yahoo.com")
CONN.login("ashashishpoojala@yahoo.com", "ashoksivakumar")
status,messages = CONN.select("INBOX")
status, response = CONN.status('INBOX', "(UNSEEN)")
unreadcount = int(response[0].split()[2].strip(').,]'))
print "UNREAD COUNT",unreadcount
date = (datetime.date.today() - datetime.timedelta(1)).strftime("%d-%b-%Y")
print date
(typ,data1)=CONN.uid('search', ('UNSEEN'), '(HEADER Subject "Build failed in Jenkins")','(SENTSINCE {0})'.format(date))
print "data1",data1
for i in data1:
	if i:
		#import subprocess
		email_message = email.message_from_string(raw_email_string)
		subject = str(email.header.make_header(email.header.decode_header(email_message['Subject'])))
		print subject
		import os
		import turtle
		turtle.write(subject,align='center',font=('Arial',50,'normal'))
		store = turtle.Screen()
		store.bgcolor("violet")
		os.system('echo "build error mail came,please check" | festival --tts')
		#subprocess.call(['speech-dispatcher'])
		#subprocess.call(['spd-say','"build error mail"'])
		#from espeak import espeak
		#espeak.synth("build error mail came")
		raw_input("enter")

