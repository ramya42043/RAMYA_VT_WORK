#!/bin/sh
while read line
do
echo $line
done <ramya.txt
echo "enter string:"
read -p "String=>" str
echo $str
sed -i "s/$str//g" ramya.txt
echo $?
cat ramya.txt
