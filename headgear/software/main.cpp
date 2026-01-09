#include <opencv2/opencv.hpp>
#include <iostream>

cv::Mat create_placeholder_frame(int width, int height, const std::string& message) {
    cv::Mat frame(height, width, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::putText(frame, message, cv::Point(50, 100), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
    return frame;
}

int main() {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error opening camera" << std::endl;
        return 1;
    }
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

    double width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    double height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    std::cout << "Camera resolution set to: " << width << "x" << height << std::endl;

    cv::Mat frame;

    while (true) {
        cap >> frame;

        if (frame.empty()) {
            frame = create_placeholder_frame(1280, 720, "Camera: No Signal");
            cap.release();
            cap.open(0);
            cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
            cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
            continue;
        }

        cv::imshow("Camera Feed", frame);
        if (cv::waitKey(5) == 27) { // Exit on ESC key
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
