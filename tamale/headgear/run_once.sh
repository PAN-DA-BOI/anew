sudo apt-get install libopencv-dev libx11-dev
gcc main.c -o main `pkg-config --cflags --libs opencv4` -lX11 -lpthread
