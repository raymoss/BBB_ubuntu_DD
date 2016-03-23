#!/bin/sh
PATH=$PATH:/usr/bin:/bin:/sbin:/usr/sbin
FILE_FOLDER=/home/ray/github/BBB_ubuntu_DD

if [ -f "$FILE_FOLDER/ip_log.txt" ]
then
	echo "hello 1s"	
	PRE_IP=$( cat $FILE_FOLDER/ip_log.txt | grep "Current public ip" | cut -d ":" -f2 )
	echo $PRE_IP
	NEW_IP=$( wget http://ipinfo.io/ip -qO - )
	echo $NEW_IP	
	if [ $NEW_IP = $PRE_IP ]
	then
		logger "GET_IP:IP is same , no need to send mail"		
		echo "IP is same . NO need to send mail"
		return 0
	fi
fi	
	
	
rm $FILE_FOLDER/ip_log.txt
touch ${FILE_FOLDER}/ip_log.txt
LOC_IP=ifconfig eth0 | grep "inet addr" | cut -d: -f2 | cut -d " " -f1
echo "Subject: BBB IP address \n Current local ip : $LOC_IP \n Current public ip : $NEW_IP \n" > $FILE_FOLDER/ip_log.txt
ssmtp raymogg123@gmail.com < $FILE_FOLDER/ip_log.txt
sleep 5
echo "Success"
logger "GET_IP:Mail sent successfully"
