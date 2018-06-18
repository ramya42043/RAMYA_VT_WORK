#!/bin/bash
#4_fibnacc.sh
num1=0
num2=1
res=1
echo "numbers are:"
if [ "$#" -ne 0 ]
then
	for((num=1;num<="$1";num++))
	do
		echo -n " $num2"
		num1=$num2
		num2=$res
		res=`expr $num1 + $num2`
	done
else
	for((num=1;num<=5;num++))
	do
		echo -n " $num2"
		num1=$num2
		num2=$res
		res=`expr $num1 + $num2`
	done
fi
echo
