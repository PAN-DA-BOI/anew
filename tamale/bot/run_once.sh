# set static ip

# open ports 5563 and 3677

sudo apt-get install libwiringpi-dev libopencv-dev gstreamer1.0-plugins-good libgstreamer1.0-dev
gcc main.c -o main -lwiringPi -lpthread -lopencv_core -lopencv_highgui -lgstapp-1.0 -lgstvideo-1.0 -lgstrtp-1.0
