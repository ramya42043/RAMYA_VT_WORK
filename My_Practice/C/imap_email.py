import imaplib

imap_host = 'imap.gmail.com'
imap_user = 'ashashishpoojala@gmail.com'
imap_pass = 'ashashish88'

## open a connection 
imap = imaplib.IMAP4_SSL(imap_host)

## login
imap.login(imap_user, imap_pass)

## get status for the mailbox (folder) INBOX
folderStatus, UnseenInfo = imap.status('INBOX', "(UNSEEN)")

print folderStatus
print UnseenInfo

NotReadCounter = int(UnseenInfo[0].split()[2].strip(').,]'))
print NotReadCounter


## create a new folder
status, createFolder_response = imap.create('myFolders.xyz')

## folders list
status, folder_list = imap.list()

## list sub-folders
status, sub_folder_list = imap.list(directory='insd')

## select a specific folder
status, data = imap.select('INBOX')

## searching current folder using title keywords 
status, messages = imap.search(None, '(SUBJECT "Work Report")')
 
## fetching message header by  using message( ID)
status, msg_header = imap.fetch('1', '(BODY.PEEK[HEADER])')

## fetching the full message ( ID=1)
status, AllTheMessage= imap.fetch('1', '(RFC822)')

## moving/copying messages around folders
#status, messages  = imap.copy(msg_ids, 'myFolders.xyz')
#status, messages  = imap.move(msg_ids, 'otherFolder')
