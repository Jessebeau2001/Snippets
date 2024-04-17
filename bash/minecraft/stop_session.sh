#!/bin/bash

# Setup variables from source files
source ./config.sh

# Places and executes command in minecraft screen session
run_in_session() {
       screen -S $session_name -X stuff "$1^M"
   }

# Formats a message as tellraw command and executes it
tellraw() {
      run_in_session "tellraw @a {\"text\":\"$1\",\"bold\":false,\"color\":\"gold\"}"
  }

# Exit out out of script if no active server session found
if ! screen -list | grep -q "$session_name"; then
   echo "Cannot stop session \"$session_name\", no currenly active sessions found"
   return 0 # Return if sourced script
   exit 0 # else exit
fi

echo "Attempting to stop minecraft server session \"$session_name\""

# Warns the logged in user about future restart
#tellraw "Server restarting soon. ETA 5m"
#sleep 5m
#tellraw "Server restarting soon. ETA 1m"
#sleep 1m
#tellraw "Server restarting soon. ETA 30s"
#sleep 30
tellraw "Server restarting. ETA 10s"
sleep 5
tellraw "Server restarting. ETA 5s"
sleep 1
tellraw "Server restarting. ETA 4s"
sleep 1
tellraw "Server restarting. ETA 3s"
sleep 1
tellraw "Server restarting. ETA 2s"
sleep 1
tellraw "Server restarting. ETA 1s"
sleep 1

# Stops the server
run_in_session stop

# Waits for screen to close
bool=true
while $bool; do
   if ! screen -list | grep -q "$session_name"; then
      bool=false
   fi
   sleep .2 # Stalls loop to prevent spam
done

echo "Succesfully stopped server session $session_name"
