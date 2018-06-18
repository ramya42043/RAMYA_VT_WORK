'''
from Tkinter import *
root = Tk()

m = PanedWindow(root)
m.pack(fill=BOTH, expand=1)

text1 = Text(m, height=15, width =15)
m.add(text1) 

text2=Text(m, height=15, width=15)
m.add(text2)
'''
from blessings import Terminal

t = Terminal()

print t.bold('Hi there!')
print t.bold_red_on_bright_green('It hurts my eyes!')

with t.location(0, t.height - 1):
    print 'This is at the bottom.'

