import os
import sys
import email
import mailbox
import turtle
import imaplib
import datetime
EMAIL_ACCOUNT="ashashishpoojala@gmail.com"
EMAIL_PW = "ashashish88"
CONN = imaplib.IMAP4_SSL("imap.gmail.com")
state,secure=CONN.login(EMAIL_ACCOUNT,EMAIL_PW)
status,messages = CONN.select("INBOX")
status, response = CONN.status('INBOX', "(UNSEEN)")
unreadcount = int(response[0].split()[2].strip(').,]'))
date = (datetime.date.today() - datetime.timedelta(0)).strftime("%d-%b-%Y")
(typ,data)=CONN.uid('search', '(UNSEEN)', '(HEADER Subject "Build failed in Jenkins")','(SENTSINCE {0})'.format(date))

for i in data:
			if i:
				l = len(data[0].split())
				print "i is ",l
				for x in range(l):
					latest_email_uid = data[0].split()[x]
					print latest_email_uid
					result, email_data = CONN.uid('fetch', latest_email_uid, '(RFC822)')
					raw_email = email_data[0][1]
					raw_email_string = raw_email.decode('utf-8')	
					email_message = email.message_from_string(raw_email_string)
					subject = str(email.header.make_header(email.header.decode_header(email_message['Subject'])))
					a= turtle.write("abcd",move=True,align='center',font=('Arial',20,'normal'))
					print a
					store = turtle.Screen()
					store.bgcolor("violet")
					b = turtle.exitonclick()
					turtle.clear()
					print b
