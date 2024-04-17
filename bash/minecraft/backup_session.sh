#!/bin/bash
# Runs the neccesary script to safely backup the minecraft server

# Save starting path because source changes this
c=$PWD

# Safely stop the server
source stop_session.sh
cd $c

# Backup files
source backup.sh
cd $c

# Start server again
source start_session.sh
cd $c
