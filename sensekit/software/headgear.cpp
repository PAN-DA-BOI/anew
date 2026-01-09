#include <opencv2/opencv.hpp>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <cstring>
#include <cstdio>
#include <ctime>

#define SPI_DEVICE "/dev/spidev0.0"
#define SPI_SPEED 1000000 // 1 MHz

// SPI file descriptor
int spi_fd;

struct SensorData {
    float temp;
    float humid;
    float gas;
    float lat;
    float lng;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

void init_spi() {
    spi_fd = open(SPI_DEVICE, O_RDWR);
    if (spi_fd < 0) {
        std::cerr << "Failed to open SPI device" << std::endl;
        exit(1);
    }
    uint8_t mode = SPI_MODE_0;
    uint8_t bits = 8;
    ioctl(spi_fd, SPI_IOC_WR_MODE, &mode);
    ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &SPI_SPEED);
}

SensorData read_sensor_data() {
    SensorData data;
    uint8_t tx[sizeof(SensorData)] = {0};
    uint8_t rx[sizeof(SensorData)] = {0};
    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = sizeof(SensorData),
        .delay_usecs = 0,
        .speed_hz = SPI_SPEED,
        .bits_per_word = 8,
    };
    ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr);
    std::memcpy(&data, rx, sizeof(SensorData));
    return data;
}

cv::Mat create_placeholder_frame(int width, int height, const std::string& message) {
    cv::Mat frame(height, width, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::putText(frame, message, cv::Point(50, 100), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
    return frame;
}

int main() {
    init_spi();

    // Start only one camera
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error opening camera" << std::endl;
        return 1;
    }

    cv::Mat frame;
    cv::Scalar text_color(0, 255, 0);

    while (true) {
        // Capture frame from the single camera
        cap >> frame;

        if (frame.empty()) {
            frame = create_placeholder_frame(640, 480, "Camera: No Signal");
            cap.release();
            cap.open(0);
        }

        // Read sensor data
        SensorData data;
        try {
            data = read_sensor_data();
        } catch (...) {
            data.temp = data.humid = data.gas = 0;
            data.lat = 37.7749;
            data.lng = -122.4194;
            data.year = 2026;
            data.month = data.day = 1;
            data.hour = data.minute = data.second = 0;
        }

        // Format sensor data
        char date_str[20], time_str[20], lat_str[20], lng_str[20], temp_str[20], humid_str[20];
        snprintf(date_str, sizeof(date_str), "%04d-%02d-%02d", data.year, data.month, data.day);
        snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d", data.hour, data.minute, data.second);
        snprintf(lat_str, sizeof(lat_str), "%.6f", data.lat);
        snprintf(lng_str, sizeof(lng_str), "%.6f", data.lng);
        snprintf(temp_str, sizeof(temp_str), "%.1f°F", data.temp);
        snprintf(humid_str, sizeof(humid_str), "%.1f%%", data.humid);

        // Overlay sensor data on the frame
        cv::putText(frame, std::string("DATE: ") + date_str, cv::Point(10, 450), cv::FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2);
        cv::putText(frame, std::string("TIME: ") + time_str, cv::Point(10, 480), cv::FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2);
        cv::putText(frame, std::string("HUMID: ") + humid_str, cv::Point(10, 510), cv::FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2);
        cv::putText(frame, std::string("LAT: ") + lat_str, cv::Point(frame.cols - 200, 450), cv::FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2);
        cv::putText(frame, std::string("LNG: ") + lng_str, cv::Point(frame.cols - 200, 480), cv::FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2);
        cv::putText(frame, std::string("TEMP: ") + temp_str, cv::Point(frame.cols - 200, 510), cv::FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2);

        // Display the frame
        cv::imshow("Camera Feed", frame);
        if (cv::waitKey(5) == 27) {
            break;
        }
    }

    // Release resources
    cap.release();
    close(spi_fd);
    cv::destroyAllWindows();
    return 0;
}
