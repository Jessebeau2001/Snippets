#!/bin/bash

# Setup variables from source file
source ./config.sh

# Exit if there already exits an active server session
if screen -list | grep -q "$session_name"; then
   echo "Cannot start new minecraft server under \"$session_name\", session already exists"
   exit 1
fi

echo "Start new minecraft server session as $session_name"

# Navigate to server dir
cd $server_dir
# Initialize new detatched screen with name and run command in it
screen -dmS $session_name sh start.sh
