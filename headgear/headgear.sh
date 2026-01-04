#!/bin/bash

echo "Updating and upgrading system..."
apt-get update && apt-get upgrade -y

mv ./anew/headgear/ /
rm -rf ./anew/

#Terran, this is where the window manager needs to be installed and set up so that "/headgear/software/pi/main" is the only thing that boots up onscreen
apt-get install i3





#################################################################################################



#REUSABLE SERVICE MAKER SO I DONT HAVE TO FIND THAT FORUM EVERYTIME
SERVICE_NAME="control"
EXECUTABLE_PATH="/headgear/software/pi/support"  # replace with the actual path
SERVICE_FILE="/etc/systemd/system/$SERVICE_NAME.service"

echo "[Unit]
Description=$SERVICE_NAME
After=network.target

[Service]
Type=simple
User=root
ExecStart=$EXECUTABLE_PATH
Restart=always
RestartSec=5

[Install]
WantedBy=multi-user.target" | sudo tee "$SERVICE_FILE" > /dev/null

sudo systemctl daemon-reload
sudo systemctl enable "$SERVICE_NAME"
sudo systemctl start "$SERVICE_NAME"

echo "Service status:"
sudo systemctl status "$SERVICE_NAME" --no-pager
#END OF REUSABLE SERVICE SCRIPT

#################################################################################################
#REUSABLE SERVICE MAKER SO I DONT HAVE TO FIND THAT FORUM EVERYTIME
SERVICE_NAME="eyes"
EXECUTABLE_PATH="/headgear/software/pi/main"  # replace with the actual path
SERVICE_FILE="/etc/systemd/system/$SERVICE_NAME.service"

echo "[Unit]
Description=$SERVICE_NAME
After=network.target

[Service]
Type=simple
User=root
ExecStart=$EXECUTABLE_PATH
Restart=always
RestartSec=5

[Install]
WantedBy=multi-user.target" | sudo tee "$SERVICE_FILE" > /dev/null

sudo systemctl daemon-reload
sudo systemctl enable "$SERVICE_NAME"
sudo systemctl start "$SERVICE_NAME"

echo "Service status:"
sudo systemctl status "$SERVICE_NAME" --no-pager
#END OF REUSABLE SERVICE SCRIPT




