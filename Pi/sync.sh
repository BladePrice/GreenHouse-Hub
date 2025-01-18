#!/bin/bash

get_from="/home/sky/Documents/GreenHouse/Pi/"
user="sky"
ip="192.168.1.10"
push_to="/home/sky/"

clear

read -sp "Password for remote: " pass

clear

ping -c 1 $ip > /dev/null 2>&1
if [ $? -ne 0 ]; then
  echo "Green House is not online"
  exit 1
fi

sshpass -p "$pass" ssh "$user@$ip" 'sudo systemctl stop http_server.service'
if [ $? -ne 0 ]; then
  echo "HTTP Server shutdown failed"
  exit 2
fi

sshpass -p "$pass" rsync -avz --exclude="sync.sh" "$get_from" "$user@$ip:$push_to"

sshpass -p "$pass" ssh "$user@$ip" 'sudo systemctl start http_server.service'
if [ $? -ne 0 ]; then
  echo "Failed to restart HTTP Server"
  exit 3
fi

echo "Files Sent and server successfully restarted."
