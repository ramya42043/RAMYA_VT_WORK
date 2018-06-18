#!/bin/bash
#files.sh
file_c=0
dir_c=0
echo "Enter specific directory:"
read -p "Path=>" path
cd $path
eval pwd
for file in `ls`
do
	if [[ -f $file ]]
	then
		file_c=`expr $file_c + 1`
	fi
	if [[ -d $file ]]
	then
		dir_c=`expr $dir_c + 1`
	fi  
done
echo "file count :"$file_c
echo "Directory count :"$dir_c
