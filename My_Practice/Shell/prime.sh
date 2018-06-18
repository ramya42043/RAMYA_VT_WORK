#!/bin/bash
echo "Enter the min Start of range:"
read -p "Min=>" min
echo "Enetr the max range:"
read -p "Max=>" max
for((index1=1;index1<=$max;index1++))
do
flag=0
for((index2=2;index2<=`expr $i / 2`;index2++))
do
if [ `expr $index1 % $index2` -eq 0 ]
then
flag=1
fi
done
if [ $flag -eq 0 ]
then
echo "$index1"
fi
done
