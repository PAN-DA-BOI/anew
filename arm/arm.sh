#!/bin/bash

echo "Updating and upgrading system..."
apt-get update && apt-get upgrade -y

mv ./anew/arm/ /
rm -rf ./anew/

##REUSABLE SERVICE MAKER SO I DONT HAVE TO FIND THAT FORUM EVERYTIME
#SERVICE_NAME="name"
#EXECUTABLE_PATH="path/to/thing"  # replace with the actual path
#SERVICE_FILE="/etc/systemd/system/$SERVICE_NAME.service"

#echo "[Unit]
#Description=$SERVICE_NAME
#After=network.target

#[Service]
#Type=simple
#User=root
#ExecStart=$EXECUTABLE_PATH
#Restart=always
#RestartSec=5

#[Install]
#WantedBy=multi-user.target" | sudo tee "$SERVICE_FILE" > /dev/null

#sudo systemctl daemon-reload
#sudo systemctl enable "$SERVICE_NAME"
#sudo systemctl start "$SERVICE_NAME"

#echo "Service status:"
#sudo systemctl status "$SERVICE_NAME" --no-pager
##END OF REUSABLE SERVICE SCRIPT



sudo apt-get install unzip -y
sudo wget https://files.waveshare.com/upload/8/8d/LCD_Module_RPI_code.zip
sudo unzip ./LCD_Module_RPI_code.zip 
cd LCD_Module_RPI_code/RaspberryPi/c
sudo make clean
sudo make -j 8
sudo ./main 2