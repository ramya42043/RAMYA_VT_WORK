import imaplib
log = imaplib.IMAP4_SSL('imap.gmail.com')
s1,s2 = log.login('ashashishpoojala@gmail.com','ashoksivakumar')
print s1,s2
Status,Messages = log.select("INBOX")
print Status,Messages
r = log.myrights("INBOX")
print r

