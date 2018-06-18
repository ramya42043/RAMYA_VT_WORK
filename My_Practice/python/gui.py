#!/usr/bin/python
import sys
from PyQt4 import QtGui


class MultiWindows(QtGui.QMainWindow):

    def __init__(self):

        self.__windows = []

    def addwindow(self, window):
        self.__windows.append(window)

    def show(self):
        for current_child_window in self.__windows:
             current_child_window.exec_() # probably show will do the same trick

class PlanetApp(QtGui.QDialog):
    def __init__(self, parent, planet):
       QtGui.QDialog.__init__(self, parent)
       # do cool stuff here

if __name__=="__main__":
    import sys # really need this here??

    app = QtGui.QApplication(sys.argv)

    jupiter = PlanetApp(None, "jupiter")
    venus = PlanetApp(None, "venus")
    windows = MultiWindows()
    windows.addwindow(jupiter)
    windows.addwindow(venus)

    windows.show()
    app.exec_()




