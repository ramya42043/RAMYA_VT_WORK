#!/usr/bin/pyhton
#Question:

input_str = raw_input()
print input_str
dimensions=[int(x) for x in input_str.split(',')]
rowNum=dimensions[0]
colNum=dimensions[1]
multilist = [[0 for col in range(colNum)] for row in range(rowNum)]
#print multilist
for row in range(rowNum):
    for col in range(colNum):
        multilist[row][col]= row*col

print multilist
