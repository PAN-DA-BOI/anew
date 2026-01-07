#!/bin/bash

echo "Updating and upgrading system..."
sudo apt-get update && sudo apt-get upgrade -y

mv ./anew/headgear/software/* /root/files
rm -rf ./anew/
cd /root/files/

#install all the nessisary packages
sudo apt install libopencv-dev python3-opencv
sudo apt install libspi-dev
sudo apt install build-essential g++
  sudo usermod -aG video,spi $USER

g++ -o main /root/files/main.cpp `pkg-config --cflags --libs opencv4`


#Terran, this is where the window manager needs to be installed and set up so that "/root/files/software/main" is the only thing that boots up onscreen
apt-get install i3





#################################################################################################



#REUSABLE SERVICE MAKER SO I DONT HAVE TO FIND THAT FORUM EVERYTIME
SERVICE_NAME="control"
EXECUTABLE_PATH="/root/files/support"  # replace with the actual path
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
EXECUTABLE_PATH="/root/files/main"  # replace with the actual path
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

echo "Rebooting to apply changes..."
sudo reboot
