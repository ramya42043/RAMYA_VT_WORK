#!/bin/bash
#calculator.sh
echo "enter numbers:"
read -p "number1-->:" number1
read -p "number2-->:" number2
echo "1.Add 2.sub 3.mul 4.division 5.modulus 6:quit"
while ((1))
do
#echo "enter choice"
read -p "choice-->" choice
case $choice in
	1) echo "Addition= `expr $number1 + $number2`";;
	2) echo "subtraction = `expr $number1 - $number2`";;
	3) echo "Multiplication = `expr $number1 \* $number2`";;
	4) echo "Division = `expr $number1 / $number2`";;
	5) echo "Modulus = `expr $number1 % $number2`";;
	6) break
esac
done
