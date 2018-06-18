#!/usr/bin/python
import imaplib
import datetime
import email
import mailbox
def alarm_popup():
	CONN = imaplib.IMAP4_SSL("imap.mail.yahoo.com")
	CONN.login("ashashishpoojala@yahoo.com", "ashoksivakumar")
	status,messages = CONN.select("INBOX")
	status, response = CONN.status('INBOX', "(UNSEEN)")
	unreadcount = int(response[0].split()[2].strip(').,]'))
	print "UNREAD COUNT",unreadcount
	date = (datetime.date.today() - datetime.timedelta(0)).strftime("%d-%b-%Y")
	print date
	(typ,data1)=CONN.uid('search', ('UNSEEN'), '(HEADER Subject "Build failed in Jenkins")','(SENTSINCE {0})'.format(date))
	print "data1",data1
	for i in data1:
		if i:
			#import subprocess
			i = len(data1[0].split())
			for x in range(i):
				latest_email_uid = data1[0].split()[x]
				result, email_data = CONN.uid('fetch', latest_email_uid, '(RFC822)')
				raw_email = email_data[0][1]
				raw_email_string = raw_email.decode('utf-8')	
				email_message = email.message_from_string(raw_email_string)
				subject = str(email.header.make_header(email.header.decode_header(email_message['Subject'])))
				import os
				import turtle
				turtle.write(subject,move=True,align='center',font=('Arial',20,'normal'))
				store = turtle.Screen()
				store.bgcolor("violet")
				with open("Output.txt", "w") as text_file:
					text_file.write("%s" % subject)
					text_file.close()
				os.system('festival --tts Output.txt')
				os.remove('Output.txt')
	
alarm_popup()
