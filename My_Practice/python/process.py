#!/usr/bin/python
import Tkinter as tk

class application(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)
        self.textbox = tk.Text(self)
        self.textbox.pack()
        self.submitbutton = tk.Button(self, text="OK", command=self.showinputtext)
        self.submitbutton.pack()
        self.mainloop()

    def showinputtext(self):
	
        self.thetext = self.textbox.get("1.0", "end-1c")
        print "You typed:", self.thetext
        self.destroy()

# Launch the GUI
app = application()

# Access the entered text after closing the GUI
print "you entered:", app.thetext
