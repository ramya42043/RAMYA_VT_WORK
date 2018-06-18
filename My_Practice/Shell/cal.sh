#!/bin/bash
echo "Enetr the two number to do mathematical operation:"
read -p "Number1=>" number1
read -p "Number2=>" number2
echo "Enetr the choice 1] Add 2]Sub 3]mul 4]Div "
read -p "Choice=>" choice
case "$choice" in
Add | add) echo "Addtion = `expr $number1 + $number2`";;
Sub | sub) echo "Substration= `expr $number1 - $number2`";;
Mul| mul) echo " Multiplication= `expr $number1 \* $number2`";;
Div | div) echo "Division= `expr $number1 / $number2`";;

