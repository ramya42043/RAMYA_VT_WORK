import inflect
convert=inflect.engine()

keys_in_dict=[]
values_in_dict=[]
for numb in range(1,101):
    values_in_dict.append(numb)
    word=convert.number_to_words(numb)
    keys_in_dict.append(word)

for word in keys_in_dict:
    print word
for val in values_in_dict:
    print val

dict_of_numbers=dict(zip(keys_in_dict,values_in_dict))
print type(dict_of_numbers)
print "all dict items"
print dict_of_numbers.items()
print "all keys"
print dict_of_numbers.keys()
print "all values"
print dict_of_numbers.values()

#print the keys:
for key in dict_of_numbers :
    print key

#print the values:
for value in dict_of_numbers.itervalues():
    print value

#print key and values
for key, value in dict_of_numbers.iteritems():
    print key, value
