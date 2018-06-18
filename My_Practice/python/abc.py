import sys
from PyQt4.QtGui import *
from PyQt4.QtCore import *

app = QApplication(sys.argv)
msg = QMessageBox()
msg.setIcon(QMessageBox.Information)
msg.setText("This is a message box")
msg.setWindowTitle("MessageBox demo")
msg.setStandardButtons(QMessageBox.Ok)
msg.exec_()
sys.exit(app.exec_())





