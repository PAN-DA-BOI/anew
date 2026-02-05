//create a window to recive camera feed: 1080X1920

//when WASD IJKL TY are pressed send that info to the pi port 3677


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <opencv2/opencv.hpp>

#define HOST "192.168.1.73" // Replace with your Pi's IP
#define COMMAND_PORT 3677
#define VIDEO_PORT 5563

int command_socket;
Display *display;
Window window;
GC gc;

void setup_window() {
    display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    int screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0, 1920, 1080, 1, BlackPixel(display, screen), WhitePixel(display, screen));
    XMapWindow(display, window);
    XFlush(display);
    gc = DefaultGC(display, screen);
}

void* video_feed(void* arg) {
    cv::VideoCapture cap("udpsrc port=5563 ! application/x-rtp,encoding-name=JPEG,payload=26 ! rtpjpegdepay ! jpegdec ! appsink", cv::CAP_GSTREAMER);
    if (!cap.isOpened()) {
        std::cerr << "Error opening video stream" << std::endl;
        return NULL;
    }

    cv::namedWindow("Bot Camera Feed", cv::WINDOW_NORMAL);
    cv::resizeWindow("Bot Camera Feed", 1920, 1080);

    cv::Mat frame;
    while (1) {
        cap >> frame;
        if (frame.empty()) break;
        cv::imshow("Bot Camera Feed", frame);
        if (cv::waitKey(1) == 'q') break;
    }
    cap.release();
    cv::destroyAllWindows();
    return NULL;
}

void send_command(char* command) {
    send(command_socket, command, strlen(command), 0);
}

void* keyboard_listener(void* arg) {
    while (1) {
        char key;
        scanf(" %c", &key);
        switch (key) {
            case 'w': send_command("W"); break;
            case 's': send_command("S"); break;
            case 'a': send_command("A"); break;
            case 'd': send_command("D"); break;
            case 'i': send_command("I"); break;
            case 'k': send_command("K"); break;
            case 'j': send_command("J"); break;
            case 'l': send_command("L"); break;
            case 't': send_command("T"); break;
            case 'y': send_command("Y"); break;
            case 27:  send_command("STOP"); return NULL; // ESC key
        }
    }
}

int main() {
    setup_window();

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(COMMAND_PORT);
    inet_pton(AF_INET, HOST, &server_addr.sin_addr);

    command_socket = socket(AF_INET, SOCK_STREAM, 0);
    connect(command_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

    pthread_t video_thread, keyboard_thread;
    pthread_create(&video_thread, NULL, video_feed, NULL);
    pthread_create(&keyboard_thread, NULL, keyboard_listener, NULL);

    pthread_join(video_thread, NULL);
    pthread_join(keyboard_thread, NULL);

    close(command_socket);
    XCloseDisplay(display);
    return 0;
}
