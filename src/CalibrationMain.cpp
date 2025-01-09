#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <spdlog/spdlog.h>

int main() {
    spdlog::info("calibrating");
    cv::VideoCapture cap(0);

    while(true) {
        cv::Mat frame;
        cap >> frame;
        cv::imshow("Frame", frame);
        cv::waitKey(1);
    }

    return 0;
}