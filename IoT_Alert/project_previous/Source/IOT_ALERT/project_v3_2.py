#!/usr/bin/python

import imaplib
import datetime
import email
import mailbox
import sys
import os
import time
import thread	
import threading
import pygame
import json
from Tkinter import *
Root = Tk()
m = PanedWindow(Root)
close_stop = True
CloseButton = Button(Root, text="Close", command=Root.destroy)
CloseButton.pack()
def Credentials():
	'''This function will take input from a .txt file(credentials.txt) '''
	dictionary = json.load(open("credentials.txt"))
	Imap = dictionary["domain"]
	Account = dictionary["account"]
	Password = dictionary["password"]
	Timer = dictionary["timer"]
	Interaction = dictionary["interaction"]
	return Imap, Account, Password,Timer,Interaction
	

def Flashing(Root,clr,Box):
	'''To Flash the popup window.
		Arguments:Root---->TK module instance
				  clr------>Background colour
				  Box------>Popup Window Specifications
	'''
	CurrentColor = Box.cget("background")
	NextColor = clr if CurrentColor == "black" else "black"
	Box.config(background=NextColor)
	Root.after(500, Flashing,Root,clr,Box)
	return None

def PopUp(Subject,clr,State,Timer=0):
	'''This function will show a message on popup with the subject,which is present in the mail
	   Arguments: Subject---->Extracted information from the mail
				  clr--------->Background colour
				  State------->Build Pass or Fail
	   			  Timer------>How much time you want to show popup
	'''
	global Root
	global m
	global close_stop
	close_stop = True
	try:
		if State == "Pass":
			Root.title("Success")
		elif State == "Fail":
			Root.title("Error")
	except:
		Root = Tk()
		m = PanedWindow(Root)
		#CloseButton = Button(Root, text="Close", command=Root.destroy)
		#CloseButton.pack()
		if State == "Pass":
			Root.title("Success")
		elif State == "Fail":
			Root.title("Error")	
	WindowSpec = Canvas(Root,width=500,height=500,bg=clr)
	WindowSpec.pack(side="top", fill="both", expand=True)
	TextSpec = WindowSpec.create_text(250,250,anchor="center",fill="orange",font=("TimesNewRoman",15))
	WindowSpec.itemconfig(TextSpec,text=Subject)
	CloseButton = Button(Root, text="Close", command=WindowSpec.destroy)
	CloseButton.pack()
	#WindowSpec.pack()
	m.add(WindowSpec)
	m.pack(fill=BOTH, expand=1)
	if State == "Fail":
		Flashing(Root,clr,WindowSpec)
	if Timer != 0:
		Root.after(Timer*1000, lambda: Root.destroy())
	try:
		WindowSpec.mainloop()
		CloseButton.destroy()
	except:
		pass
		print "root"
	close_stop = False
	return None

	
def Alarm(State,Timer=0):
	'''This function will play an alarm sound with the subject,which is present in the mail
		Arguments: State---->Build pass or fail
	   			   Timer------>How much time you want to play alarm
	'''
	if State == "Pass":
		return None
	pygame.mixer.init()
	Var = pygame.mixer.Sound('notification.mp3')
	if Timer == 0 :
		while close_stop==True:
			Var.play()
		Var.stop()
	else:
		Now = time.time()
		After = time.time()
		while After-Now < Timer:
			Var.play()
			After= time.time()
		Var.stop()
	return None
	
def ExtractMail(Conn,MailStringAddress,Interaction,Timer,clr,State):
	'''This function will get the unique id's of unread mails.It will extract the each mail subject.
	Arguments:conn----->Mail login instance
	MailStringAddress--->Unique id's of unread mails
	Interaction------>If user wants close manually("Yes")
	Timer----->To close the popup and alarm after certain time
	clr------->Background colour
	State----->Build pass or fail'''
	for StringAddress in MailStringAddress:
		if StringAddress:
			l = len(MailStringAddress[0].split())
			for IntAddress in range(l):
				LatestEmailUid = MailStringAddress[0].split()[IntAddress]
				Subject = "None"
				while Subject == "None":
					LatestEmailUid = MailStringAddress[0].split()[IntAddress]
					try:
						Result, EmailData = Conn.uid('fetch', LatestEmailUid, '(RFC822)')
					except:
						PopUp(Root,"Domain server issue",1)
						os._exit(1)
					RawEmail = EmailData[0][1]
					RawEmailString = RawEmail.decode('utf-8')
					EmailMessage = email.message_from_string(RawEmailString)
					Subject = str(email.header.make_header(email.header.decode_header(EmailMessage['Subject'])))
				if Interaction == "Yes":
					ArgumentsAlarm = (State,)
					ArgumentsScreen = (Subject,clr,State)
				else:
					ArgumentsAlarm=(State,Timer)
					ArgumentsScreen = (Subject,clr,State,Timer)
				if ("DISPLAY" in os.environ):
					Threads = []
					ThrVar1 = threading.Thread(target=PopUp,args=ArgumentsScreen)
					ThrVar2 = threading.Thread(target=Alarm,args=ArgumentsAlarm)
					ThrVar1.start()
					ThrVar2.start()
					Threads.append(ThrVar1)
					Threads.append(ThrVar2)
					for Thr in Threads:
						Thr.join()
				else:
					Alarm(State,Timer)
				break
	return None

def EmailClient():
	'''This function will login with the credentilas given by the user.
		Selects INBOX to read UNSEEN messages.
		In Unseen messages If the subject is belonging to Jenkins or Bild Success in Jenkins then it will call alarm and popup functions
	'''
	Imap,EmailAccount, EmailPw,Timer,Interaction = Credentials()
	if Interaction ==  "Yes":
		Timer = 0
	try:
		Conn = imaplib.IMAP4_SSL(Imap)
		State,Secure=Conn.login(EmailAccount,EmailPw)
	except imaplib.IMAP4.error:
		PopUp("LOGIN FAILED!!!,username or password is incorrect","violet","Fail", 1)
		os._exit(1)
	except imaplib.socket.gaierror:
		PopUp("no internet connection","violet","Fail",1)
		os._exit(1)
	except:
		PopUp("IMAPLIB ERROR","violet","Fail", 1)
		os._exit(1)

	if State == 'OK':	
		Status,Messages = Conn.select("INBOX")
		if Status != 'OK':
			return None
		Status, Response = Conn.status('INBOX', "(UNSEEN)")
		if Status != 'OK':
			return None
		UnreadCount = int(Response[0].split()[2].strip(').,]'))
		print UnreadCount
		if UnreadCount == 0:
			return None
		Date = (datetime.date.today() - datetime.timedelta(0)).strftime("%d-%b-%Y")
		'''To get unique Ids of unseen mails subject which is matched with build failed in jenkins only today'''
		(Typ,BuildFailStringAddress)=Conn.uid('Search', '(UNSEEN)','(HEADER Subject "Build failed in Jenkins")')
		if Typ == 'OK':
			ExtractMail(Conn,BuildFailStringAddress,Interaction,Timer,"red","Fail")
		else :
			PopUp(Root,"Domain server issue","violet","Fail",1)
			os._exit(1)
		(Typ,BuildPassStringAddress)=Conn.uid('search', '(UNSEEN)','(HEADER Subject "Build Success in Jenkins")')
		if Typ == 'OK':
			ExtractMail(Conn,BuildPassStringAddress,Interaction,Timer,"green","Pass")
		else:
			PopUp("Domain server issue","violet","Fail",1)
			os._exit(1)
	print Conn.logout()
	return None
if __name__ == "__main__":					
	while True:
		thread.start_new_thread(EmailClient,())
		time.sleep(1)
#		EmailClient()
