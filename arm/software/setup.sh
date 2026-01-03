#!/bin/bash

echo "Updating and upgrading system..."
apt-get update && apt-get upgrade -y


apt-get install -y python3 python3-pip

pip3 install --upgrade pip
pip3 install -r requirements.txt