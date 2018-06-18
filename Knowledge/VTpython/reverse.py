def reverse(data_list):
    		length = len(data_list)
   		s = length
    		new_list = [None]*length
    		for item in data_list:
       			s = s - 1
        		new_list[s] = item
    		return new_list


list1=[1,2,3,4,5]
list2=reverse(list1)
print list2
