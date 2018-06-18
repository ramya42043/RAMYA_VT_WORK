from Tkinter import *
def roots():
	Root = Tk()
	WindowSpec = Canvas(Root,bg=clr,height=150,width=400)
	CloseButton = Button(Root, text="Close", command=Root.destroy)
	WindowSpec.pack()
	CloseButton.pack()
