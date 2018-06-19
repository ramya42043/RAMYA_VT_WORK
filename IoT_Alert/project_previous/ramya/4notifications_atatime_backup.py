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

row=2
colum=2
close_stop = True
list_global = []
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
	Root.after(1000, Flashing,Root,clr,Box)
	return None


def PopUp(Subject,clr,State,Timer=0):
	'''This function will show a message on popup with the subject,which is present in the mail
	   Arguments: Subject---->Extracted information from the mail
				  clr--------->Background colour
				  State------->Build Pass or Fail
	   			  Timer------>How much time you want to show popup
	'''
	if ("DISPLAY" in os.environ) == False:
		return

	global close_stop
	close_stop = True
	Root = Tk()
	Root.geometry('{}x{}'.format(Root.winfo_screenwidth(),Root.winfo_screenheight()))
	cl = Button(Root,text="close",command=Root.destroy)
	cl.pack(side="bottom")
	print "Popup  start close_stop",close_stop
	frame = Frame(Root, width=1440, height=900)
	frame.pack()
	k = 0
	length = len(Subject)
	print "length",length
	for i in range(row):
		for j in range(colum):
			if k >= length:
				break
			top = Toplevel(Root,bd=2)
			canvas = Canvas(top,bg=clr,width=Root.winfo_screenwidth()/3,height=Root.winfo_screenheight()/3)
			Text=canvas.create_text(Root.winfo_screenwidth()/6,Root.winfo_screenheight()/6)
			canvas.itemconfig(Text,text=Subject[k])
			canvas.pack()
			width=((Root.winfo_screenwidth()-100)/2)
			height=((Root.winfo_screenheight()-100)/2)
			top.geometry('{}x{}+{}+{}'.format(width,height,j*(width+100),i*(height+100)))
			top.lift(aboveThis=Root)
			close = Button(top,text="close",command=top.destroy)
			close.pack()
			if State == "Pass":
				top.title("Success")
			elif State == "Fail":
				top.title("Error")
			#if State == "Fail":
			#	Flashing(Root,clr,canvas)
			k += 1
	if Timer != 0:
		Root.after(Timer*1000, lambda: Root.destroy())
	Root.mainloop()
	close_stop = False
	print "Popup end close_stop",close_stop
	return None

	
def Alarm(State,Timer=0):
	'''This function will play an alarm sound with the subject,which is present in the mail
		Arguments: State---->Build pass or fail
	   			   Timer------>How much time you want to play alarm
	'''
	if State == "Pass":
		return None
	global close_stop
	close_Stop=True
	print "alarm start close_stop",close_stop
	pygame.mixer.init()
	Var = pygame.mixer.Sound('notification.mp3')
	print "Timer value",Timer
	if Timer == 0 :
		print "alarm close_stop",close_stop
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
	list_subject = []
	for StringAddress in MailStringAddress:
		if StringAddress:
			l = len(MailStringAddress[0].split())
			if l > 4:
				l = 4
			else:
				pass
			for IntAddress in range(l):
				LatestEmailUid = MailStringAddress[0].split()[IntAddress]
				Subject = "None"
				while Subject == "None":
					LatestEmailUid = MailStringAddress[0].split()[IntAddress]
					try:
						Result, EmailData = Conn.uid('fetch', LatestEmailUid, '(RFC822)')
					except:
						PopUp(["Domain server issue"],"violet","Fail",2)
						sys.exit(1)
					RawEmail = EmailData[0][1]
					RawEmailString = RawEmail.decode('utf-8')
					EmailMessage = email.message_from_string(RawEmailString)
					Subject = str(email.header.make_header(email.header.decode_header(EmailMessage['Subject'])))
					if Subject != "None":
						list_subject.append(Subject) 
	if len(list_subject)!=0:
		if Interaction == "Yes":
			ArgumentsAlarm = (State,)
			ArgumentsScreen = (list_subject,clr,State)
		else:
			ArgumentsAlarm=(State,Timer)
			ArgumentsScreen = (list_subject,clr,State,Timer)
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
		PopUp(["LOGIN FAILED!!!,username or password is incorrect"],"violet","Fail", 2)
		sys.exit(1)
	except imaplib.socket.gaierror:
		PopUp(["No Internet Connection"],"violet","Fail",2)
		sys.exit(1)
	except:
		PopUp(["IMAPLIB ERROR"],"violet","Fail", 2)
		sys.exit(1)

	if State == 'OK':	
		Status,Messages = Conn.select("INBOX")
		if Status != 'OK':
			return None
		Status, Response = Conn.status('INBOX', "(UNSEEN)")
		if Status != 'OK':
			return None
		UnreadCount = int(Response[0].split()[2].strip(').,]'))
		if UnreadCount == 0:
			return None
		Date = (datetime.date.today() - datetime.timedelta(0)).strftime("%d-%b-%Y")
		'''To get unique Ids of unseen mails subject which is matched with build failed in jenkins only today'''
		(Typ,BuildFailStringAddress)=Conn.uid('Search', '(UNSEEN)','(HEADER Subject "Build failed in Jenkins")')
		if Typ == 'OK':
			ExtractMail(Conn,BuildFailStringAddress,Interaction,Timer,"red","Fail")
		else :
			PopUp(["Domain server issue"],"violet","Fail",2)
			sys.exit(1)
		(Typ,BuildPassStringAddress)=Conn.uid('search', '(UNSEEN)','(HEADER Subject "Build Success in Jenkins")')
		if Typ == 'OK':
			ExtractMail(Conn,BuildPassStringAddress,Interaction,Timer,"green","Pass")
		else:
			PopUp(["Domain server issue"],"violet","Fail",2)
			sys.exit(1)
	return None					
while True:
	EmailClient()

