#!/bin/bash
#5_sighand.sh
trap sigint INT
trap sigusr1 USR1
trap sigusr2 USR2
trap sigterm TERM
trap sigabrt ABRT
cnt=0
int=0
sigint()
{
	echo "Recieved SIGINT"
	int=`expr $int + 1`
	echo $int
	if [ $int -eq 2 ]
	then 
		exit
	fi
}
sigterm()
{
	echo "Recieved SIGTERM"
	exit
}
sigabrt()
{
	echo "Recieved SIGABRT"
}
sigusr1()
{
	#echo ""
	echo "Recieved SIGUSR1 or SIGUSR1"
}
sigusr2()
{
	echo "Recieved SIGUSR1 or SIGUSR1"
}
ps -f
while :
do
	sleep 3
	echo -n $cnt
	cnt=`expr $cnt + 1`

done
