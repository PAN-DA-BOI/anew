// open port 5563 for video stream out
// listen on port 3677 for commands in 


//parse input info: WASD IJKL TY

// forward 		- W/up arrow
// backward 	- S/down arrow
// steer left 	- A/left arrow
// steer right 	- D/right arrow

// camera up 	- I/top D-pad
// camera down 	- k/top D-pad
// camera left 	- j/top D-pad
// camera right	- l/top D-pad

// start recording	- T/right trigger
// take picture 	- Y/left trigger

// movment functions

// camera movment

// camera start recording 

// camera take picture


// pinout:
// all servos (i2c connection) 	:	signal pin	- 0x14
// rear motor1					:	digital pin	- GPIO23
// rear motor2					:	digital pin	- GPIO24





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define I2C_ADDR 0x14
#define I2C_BUS "/dev/i2c-1"
#define COMMAND_PORT 3677
#define VIDEO_PORT 5563

int i2c_fd;
int command_socket, video_socket;
int rear_motor1_pin = 23;
int rear_motor2_pin = 24;

void setup_i2c() {
    if ((i2c_fd = open(I2C_BUS, O_RDWR)) < 0) {
        perror("Failed to open I2C bus");
        exit(1);
    }
    if (ioctl(i2c_fd, I2C_SLAVE, I2C_ADDR) < 0) {
        perror("Failed to set I2C slave address");
        exit(1);
    }
}

void i2c_write_byte(uint8_t reg, uint16_t value) {
    uint8_t buf[3];
    buf[0] = reg;
    buf[1] = value & 0xFF;
    buf[2] = (value >> 8) & 0xFF;
    if (write(i2c_fd, buf, 3) != 3) {
        perror("Failed to write to I2C");
    }
}

void set_pwm_frequency(int timer, int frequency, int period) {
    uint16_t prescaler = (72000000 / ((period + 1) * frequency)) - 1;
    i2c_write_byte(0x40 + timer, prescaler);
    i2c_write_byte(0x44 + timer, period);
}

void set_pwm_value(int channel, uint16_t value) {
    i2c_write_byte(0x20 + channel, value);
}

void setup_gpio() {
    wiringPiSetupGpio();
    pinMode(rear_motor1_pin, PWM_OUTPUT);
    pinMode(rear_motor2_pin, PWM_OUTPUT);
}

void move_forward() {
    digitalWrite(rear_motor1_pin, HIGH);
    digitalWrite(rear_motor2_pin, HIGH);
}

void move_backward() {
    digitalWrite(rear_motor1_pin, LOW);
    digitalWrite(rear_motor2_pin, LOW);
}

void steer_left() {
    set_pwm_value(0, 256); // Channel 0, left position
}

void steer_right() {
    set_pwm_value(0, 512); // Channel 0, right position
}

void stop_motors() {
    digitalWrite(rear_motor1_pin, 0);
    digitalWrite(rear_motor2_pin, 0);
}

void camera_up() {
    set_pwm_value(1, 307); // Channel 1, up position
}

void camera_down() {
    set_pwm_value(1, 204); // Channel 1, down position
}

void camera_left() {
    set_pwm_value(2, 256); // Channel 2, left position
}

void camera_right() {
    set_pwm_value(2, 512); // Channel 2, right position
}

void start_recording() {
    // Implement recording logic
    system("libcamera-vid -t 0 -o video.h264 &");
}

void take_picture() {
    // Implement picture logic
    system("libcamera-jpeg -o photo.jpg");
}

void* command_listener(void* arg) {
    struct sockaddr_in address = {0};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(COMMAND_PORT);

    command_socket = socket(AF_INET, SOCK_STREAM, 0);
    bind(command_socket, (struct sockaddr *)&address, sizeof(address));
    listen(command_socket, 1);

    int conn_fd = accept(command_socket, (struct sockaddr *)NULL, NULL);
    char buffer[1024] = {0};

    while (1) {
        read(conn_fd, buffer, 1024);
        if (strcmp(buffer, "W") == 0) move_forward();
        else if (strcmp(buffer, "S") == 0) move_backward();
        else if (strcmp(buffer, "A") == 0) steer_left();
        else if (strcmp(buffer, "D") == 0) steer_right();
        else if (strcmp(buffer, "I") == 0) camera_up();
        else if (strcmp(buffer, "K") == 0) camera_down();
        else if (strcmp(buffer, "J") == 0) camera_left();
        else if (strcmp(buffer, "L") == 0) camera_right();
        else if (strcmp(buffer, "T") == 0) start_recording();
        else if (strcmp(buffer, "Y") == 0) take_picture();
        else if (strcmp(buffer, "STOP") == 0) stop_motors();
    }
}

void* video_stream(void* arg) {
    // Implement video streaming logic using GStreamer or similar
    system("gst-launch-1.0 -v libcamerasrc ! video/x-raw,width=1920,height=1080,framerate=30/1 ! \
           videoconvert ! jpegenc ! rtpjpegpay ! udpsink host=CLIENT_IP port=5563");
}

int main() {
    setup_i2c();
    setup_gpio();
    set_pwm_frequency(0, 50, 4095); // Timer 0, 50Hz, period=4095

    pthread_t command_thread, video_thread;
    pthread_create(&command_thread, NULL, command_listener, NULL);
    pthread_create(&video_thread, NULL, video_stream, NULL);

    pthread_join(command_thread, NULL);
    pthread_join(video_thread, NULL);

    return 0;
}
