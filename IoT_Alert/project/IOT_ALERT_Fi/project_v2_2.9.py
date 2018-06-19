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

#from PIL import ImageTk, Image
###parent and 4 childs with alarm sync and closes only one child on parent close




parentgui_flag=0
close_flag=0
wait_flag=0
list_subject=[]
tkinter_list=[]
x1=y1=x2=y2=x3=y3=x4=y4=0
Root_warn=0
Parent_Root=0
close_Alarm=1

def Credentials():
	'''This function will take input from a .txt file(credentials.txt) '''
	dictionary = json.load(open("credentials.txt"))
	Imap = dictionary["domain"]
	Account = dictionary["account"]
	Password = dictionary["password"]
	Timer = dictionary["timer"]
	Interaction = dictionary["interaction"]
	AlarmTone = dictionary["alarmtone"]
	return Imap, Account, Password,Timer,Interaction,AlarmTone
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

def creat_child_window(Subject,index,clr,State,Timer,x,y):
	global list_subject,wait_flag,close_flag,close_Alarm,tkinter_list
	del list_subject[index]
	close_Alarm=1
	Root = Tk()
	
	wait_flag=1
	
	#tkinter_list.append(Root)
	
	
	if State == "Pass":
		Root.title("Success")
	elif State == "Fail":
		Root.title("Failure")
	WindowSpec = Canvas(Root,bg=clr,height=150,width=400)
	
	WindowSpec.pack(side="top", fill="both", expand=True)
	TextSpec = WindowSpec.create_text(250,250,anchor="center",font=("TimesNewRoman",12))
	WindowSpec.itemconfig(TextSpec,text=Subject)
	CloseButton = Button(Root, text="Close", command=Root.destroy)
	Root.geometry('%dx%d+%d+%d' % ((Root.winfo_screenwidth()/2)-38, (Root.winfo_screenheight()/2)-84,x,y))
	#645, 300
	if Timer != 0:
			Root.after(Timer*1000, lambda: Root.destroy())
	WindowSpec.pack()
	CloseButton.pack()
	
	if State == "Fail":
		Flashing(Root,clr,WindowSpec)
		Root.mainloop()
	if State == "Pass":
		Flashing(Root,clr,WindowSpec)
		Root.mainloop()
	close_Alarm=0
	
	
	wait_flag=0
	

def PopUp(Subject,clr,State,Timer=0):
	'''
		This function will show a message on popup with the subject,which is present in the mail
	   Arguments: Subject---->Extracted information from the mail
				  clr--------->Background colour
				  State------->Build Pass or Fail
	   			  Timer------>How much time you want to show popup
	'''
	global list_subject
	list_subject.append(Subject)
	
	global x1,y1,x2,y2,x3,y3,x4,y4
	
	while len(list_subject):

		for data in list_subject:
			
			if(x1==0)and(y1==0):
				x1=63;y1=81;
				index=list_subject.index(data)
				
				creat_child_window(data,index,clr,State,Timer,x1,y1)

				
				
				x1=0;y1=0;
	
			elif(x2==0)and(y2==0):
				index=list_subject.index(data)
				x2=710;y2=80
				creat_child_window(data,index,clr,State,Timer,x2,y2)

				
				x2=0;y2=0
	
			elif(x3==0)and(y3==0):
				index=list_subject.index(data)
				x3=63;y3=438
				creat_child_window(data,index,clr,State,Timer,x3,y3)
				
				
				x3=0;y3=0
			elif(x4==0)and(y4==0):
				index=list_subject.index(data)
				x4=710;y4=438
				creat_child_window(data,index,clr,State,Timer,x4,y4)
				
				
				x4=0;y4=0
			else:
				while(wait_flag!=0):
				
					pass
	return None

def Alarm(State,AlarmTone,Timer=0):
	'''This function will play an alarm sound with the subject,which is present in the mail
		Arguments: State---->Build pass or fail
	   			   Timer------>How much time you want to play alarm
	'''
	global close_Alarm
	close_Alarm=1
	
	if State == "Pass":
		return None
	pygame.mixer.init()
	
	Var = pygame.mixer.Sound(AlarmTone)
	
	while close_Alarm==1:
		Var.play()
	
	Var.stop()
	return None

def ExtractMail(Conn,MailStringAddress,Interaction,AlarmTone,Timer,clr,State):
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
				
				try:
					Result, EmailData = Conn.uid('fetch', LatestEmailUid, '(RFC822)')
				except:
					PopUp("Domain server issue","violet","Fail",Timer)
				RawEmail = EmailData[0][1]
				RawEmailString = RawEmail.decode('utf-8')	
				EmailMessage = email.message_from_string(RawEmailString)
				Subject = str(email.header.make_header(email.header.decode_header(EmailMessage['Subject'])))

				if Interaction == "Yes":
					ArgumentsAlarm = (State,AlarmTone)
					ArgumentsScreen = (Subject,clr,State)
				else:
					ArgumentsAlarm=(State,AlarmTone,Timer)
					ArgumentsScreen = (Subject,clr,State,Timer)
				if ("DISPLAY" in os.environ):
					global parentgui_flag
		
					Threads = []
					ThrVar1 = threading.Thread(target=PopUp,args=ArgumentsScreen)
					ThrVar2 = threading.Thread(target=Alarm,args=ArgumentsAlarm)
					ThrVar1.start()
					ThrVar2.start()
					Threads.append(ThrVar1)
					#Threads.append(ThrVar2)
					#for Thr in Threads:
					#	Thr.join()
				else:
					Alarm(State,Timer)
	return None

def EmailClient():
	'''This function will login with the credentilas given by the user.
		Selects INBOX to read UNSEEN messages.
		In Unseen messages If the subject is belonging to Jenkins or Bild Success in Jenkins then it will call alarm and popup functions
	'''
	Imap,EmailAccount, EmailPw,Timer,Interaction,AlarmTone = Credentials()
	try:
		Conn = imaplib.IMAP4_SSL(Imap)
		State,Secure=Conn.login(EmailAccount,EmailPw)
	except imaplib.IMAP4.error:
		PopUp("LOGIN FAILED!!!,username or password is incorrect","violet","Fail",Timer)
		sys.exit(1)
	except imaplib.socket.gaierror:
		PopUp("no internet connection","violet","Fail",Timer)
		sys.exit(1)
	except:
		PopUp("IMAPLIB ERROR","violet","Fail",Timer)
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

		(Typ,BuildFailStringAddress)=Conn.uid('search', '(UNSEEN)','(HEADER Subject "Build failed in Jenkins")')
			
		if Typ == 'OK':
			
			ExtractMail(Conn,BuildFailStringAddress,Interaction,AlarmTone,Timer,"red","Fail")
		else :
				
			PopUp("Domain server issue","violet","Fail",Timer)
			sys.exit(1)
		(Typ,BuildPassStringAddress)=Conn.uid('search', '(UNSEEN)','(HEADER Subject "Build Success in Jenkins")')
		if Typ == 'OK':
			ExtractMail(Conn,BuildPassStringAddress,Interaction,AlarmTone,Timer,"green","Pass")
		else:
			PopUp("Domain server issue","violet","Fail",Timer)
			sys.exit(1)
	Conn.logout()
	return None
		
while True:
		
	if((x1==0)or(x2==0)or(x3==0)or(x4==0)):
		EmailClient()





