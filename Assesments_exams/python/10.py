import csv
import sqlite3

mydb = sqlite3.connect("FaceBase.db")           

cursor = mydb.cursor()

csv_data = csv.reader(file('file.csv'))
for row in csv_data:

	cursor.execute('INSERT INTO People(names, \
          classes, mark )' \
          'VALUES("%s", "%s", "%s")', 
          row)
mydb.commit()
cursor.close()
print "Done"
