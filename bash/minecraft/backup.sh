#!/bin/bash

# Setup variables from source file
source ./config.sh
out_name="$(date +%Y-%m-%d) [$mc_version] (world)"

# Abort backup if server is still running
if screen -list | grep -q "$session_name"; then
   echo "Cannot backup world files while server $session_name is running"
   exit 1
fi

echo "Starting backup for $session_name"

# Navigate to server dir and start backup process
cd $server_dir
tar -czf "$out_name.tar.gz" world
mv "$out_name.tar.gz" "$backup_dir"

echo "Backed up $session_name to $backup_dir/$out_name.tar.gz"
