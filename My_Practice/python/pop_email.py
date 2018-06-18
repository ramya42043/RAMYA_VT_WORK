import email
import poplib
from email.header import decode_header

login = 'ashashishpoojala@yahoo.com'
password = 'ashoksivakumar'
pop_server = 'pop.mail.yahoo.com'
pop_port = 995

mail_box = poplib.POP3_SSL(pop_server, pop_port)
mail_box.user(login)
mail_box.pass_(password)

num_messages = len(mail_box.list()[1])
for i in range(num_messages):
    print(i, "message:")

    raw_email  = b"\n".join(mail_box.retr(i+1)[1])
    parsed_email = email.message_from_string(str(raw_email))

    subject = decode_header(parsed_email['Subject'])
    print(subject[0][0].decode(subject[0][1]))

mail_box.quit()
