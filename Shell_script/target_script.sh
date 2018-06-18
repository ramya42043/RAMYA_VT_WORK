#!/bin/bash

while ((1))
do

printf "Modules are 1.Audio 2.Display 3.Camera 4.Exit"
printf "\n"
printf "Enter your choice:"
read choice

clear

case "$choice" in
	1 ) for i in $(ls ./Audio/*.c)
	do
		gcc $i `pkg-config --cflags --libs gstreamer-1.0`
		./a.out ./Audio/song.mp3
	done ;;

	2 ) for i in $(ls ./Video/*.c)
	do
		gcc $i `pkg-config --cflags --libs gstreamer-1.0`
		./a.out ./Video/video.webm
	
	done ;;

	4 ) break ;;	
	* ) printf "\n Ur chioce is wrong "
esac
done
