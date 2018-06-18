#!/bin/bash
source ./build.sh

echo "Choose the Board to create Images"
echo "1: Dragon Board 2: Beagle Bone 3: RPI3 Board"
read choice
#$choice=$1
if [ $choice -eq 1 ]
then 
	Machine="dragonboard-410c"
	echo $Machine
elif [ $choice -eq 2 ]
then
	Machine="beaglebone"
	echo $Machine
else
	Machine="raspberrypi3"
	echo $Machine
fi

echo "Enter version for $Machine"
read version
#$version=$2
#sh ./Dir.sh $Machine $version
Create_Dir $Machine $version

