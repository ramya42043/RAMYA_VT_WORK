from Tkinter import *
root = Tk()
root.geometry('{}x{}'.format(root.winfo_screenwidth(),root.winfo_screenheight()))
cl = Button(root,text="close",command=root.destroy)
cl.pack(side="bottom")
row=2
print type(row)
column=2
for k in range(row):
        for j in range(column):
                i = Toplevel(root,bd=4,bg="green")
                canvas = Canvas(i,bg="red",width=root.winfo_screenwidth()/4,height=root.winfo_screenheight()/4)
                te=canvas.create_text(root.winfo_screenwidth()/8,root.winfo_screenheight()/8)
                canvas.itemconfig(te,text="ramya")
                canvas.pack()
                width=((root.winfo_screenwidth()-100)/2)
                height=((root.winfo_screenheight()-100)/2)
                i.geometry('{}x{}+{}+{}'.format(width,height,j*width,k*height))
                i.lift(aboveThis=root)
                close = Button(i,text="close",command=i.close)
                close.pack()
                print "ramya1"
                i.mainloop()
                print "ramya2"
                if k+j == (row+column)/2:
                        break
#root.mainloop()

'''
root = tk.Tk()

screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()

root.mainloop()

'''
