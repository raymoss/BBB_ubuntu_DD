#!/bin/sh
if [ -f "ip_log.txt" ] 
then
	rm ip_log.txt
fi
touch ip_log.txt
echo "Subject: IP address" >>ip_log.txt
echo "getting the ip" >> ip_log.txt
echo "My current ip :" >> ip_log.txt 
ifconfig wlp15s0 | grep "inet addr" | cut -d: -f2 | awk '{print $1}' >> ip_log.txt 2>&1
echo "My public ip :" >>ip_log.txt
wget http://ipinfo.io/ip -qO - >> ip_log.txt
echo "Sending mail" >>ip_log.txt
ssmtp raymogg123@gmail.com < ip_log.txt

