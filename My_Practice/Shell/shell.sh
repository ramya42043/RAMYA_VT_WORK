#/bin/bash
echo "enter array length"
read -p "length-->" length
for (( i=0;i<length;i++ ))
do
	echo "Enter `expr $i + 1`:"
	read array[$i]
done
echo "array elements are:"
for (( i=0;i<length;i++ ))
do
	echo "array[$i]=${array[$i]}"
done
for (( i=0, j=`expr $length - 1` ; i<j ; i++,j--))
do
	temp=${array[$i]}
	array[$i]=${array[$j]}
	array[$j]=$temp
done
echo "after reversing:"
for (( i=0;i<length;i++ ))
do
	echo "array[$i]=${array[$i]}"
done

