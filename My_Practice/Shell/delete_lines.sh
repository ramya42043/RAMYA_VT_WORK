#!/bin/sh
while read line
do
echo $line
done <ramya.txt
echo "enter range of lines:"
read -p "Strating=>" n1
#read -p "ending=>" n2
echo $n1 $n2
sed -i ''$n1','$n2'd' ramya.txt
#93echo $?
cat ramya.txt
