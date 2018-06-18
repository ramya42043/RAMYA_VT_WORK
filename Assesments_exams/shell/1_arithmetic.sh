#!/bin/bash
#1_arithmetic.sh
echo "enter two numbers:"
read num1
read num2
#echo $num1 $num2
echo "1.add"
echo "2.sub"
echo "3.mul"
echo "4.div"
echo "5.remainder"
echo "enter your choice:"
read choice
case $choice in
	1)echo `expr $num1 + $num2`;;
	2)echo `expr $num1 - $num2`;;
	3)echo `expr $num1 \* $num2`;;
	4)echo `expr $num1 / $num2`;;
	5)echo `expr $num1 % $num2`;;
	*)echo "invalid input"

esac
