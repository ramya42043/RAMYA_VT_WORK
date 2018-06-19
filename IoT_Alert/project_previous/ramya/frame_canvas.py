from Tkinter import *

class AllTkinterWidgets:
    def __init__(self, master):
        frame = Frame(master, width=1440, height=900)
        
        frame.pack()

        iframe5 = Frame(frame, bd=2, relief=RAISED)
        iframe5.pack(expand=1, fill=X, pady=10, padx=5)
        for i in range(4):
            c = Canvas(iframe5, bg='green', width=340, height=100)
            c.pack()
            c.create_text(260, 80, text='Canvas'+str(i), font=('verdana', 10, 'bold'))
           # raw_input("enter")
        iframe5.pack(expand=1, fill=X, pady=10, padx=5)
        close = Button(frame,text="close",command=master.destroy)
        close.pack()



    
root = Tk()
#root.option_add('*font', ('verdana', 10, 'bold'))
all = AllTkinterWidgets(root)
root.title('Tkinter Widgets')
root.mainloop()
           
       
