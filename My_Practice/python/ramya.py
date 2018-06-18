import poplib
mailServer = 'pop.mail.yahoo.com'
emailID = 'ashashishpoojala@yahoo.com'
emailPass = 'ashoksivakumar'


myEmailConnection = poplib.POP3_SSL(mailServer)

#print myEmailConnection.getwelcome()

myEmailConnection.user(emailID)

myEmailConnection.pass_(emailPass)

EmailInformation = myEmailConnection.stat()
print "Number of new emails: %s (%s bytes)" % EmailInformation

print "\n\n===\nRead messages\n===\n\n"


numberofmails = EmailInformation[0]
print numberofmails
'''for i in range(numberofmails):
	print "RANGE-------->",len(range(numberofmails))
	for email in myEmailConnection.retr(i+1)[1]:
		print email
	#	pass'''
