#/bin/bash
echo "Enter the array length:"
read -p "length=>" length
echo "Enetr the array element:"
for (( index1=0;index1< $length;index1++ ))
do
echo "Enter `expr $index1 + 1`:"
read array[$index1]
done
for(( index1=0, index2=`expr $length - 1` ; index2 > index1;index1++,index2-- ))
do
temp=${array[$index1]}
array[$index1]=${array[$index2]}
array[$index2]=$temp
done
echo "reverse array element:"
for((index1=0;index1< $length ; index1++))
do
echo "array[$index1]=${array[$index1]}"
