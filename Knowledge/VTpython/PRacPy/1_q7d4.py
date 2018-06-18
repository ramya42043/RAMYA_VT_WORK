
#!/usr/bin/pyhton


def countXX(word):
	length=len(word)
	count = 0
	for index in range(length-1):
		if (word[index]=='x')  and (word[index+1]=='x'):
			count +=1
	return count	


string= raw_input("enter the string to count XX overlapped\n")
result = countXX(string)
print result
