#!/bin/bash
filecnt=0
dircnt=0
for var in `ls`
do
	if [ -f $var ]
	then
		filecnt=`expr $filecnt + 1`
	fi
	if [ -d $var ]
	then
		dircnt=`expr $dircnt + 1`
	fi
done
echo "file count is $filecnt"
echo "dir count is $dircnt"
