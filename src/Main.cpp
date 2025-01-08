#define SPDLOG_ACTIVE_LEVEL SPDLOG_LOGGER_TRACE // 设置为输出文件名和行号

#include "Calibration.hpp"
#include <atomic>
#include <exception>
#include <mutex>
#include <spdlog/spdlog.h>

int main() {
    spdlog::set_pattern("[%H:%M:%S.%e] [%l] [%s %!:%#]  %v");
    SPDLOG_INFO("main.cpp start working.");

    // * 初始化 Image Consumer 和 Producer
    // Producer
    std::mutex mutexFrameInfo;        // 防止读写冲突
    std::atomic<bool> canRead{false}; // 原子化，保证可读
    std::thread([&]() {
        try {
            SPDLOG_INFO("start producer's thread");
            // TODO: 读取图像
            SPDLOG_INFO("closing producer's thread");
        } catch (std::exception &e) {
            SPDLOG_CRITICAL("Fatal Error: {}", e.what());
            std::exit(-1);
        }
    }).join();

    // Consumer
    std::thread([&]() {}).join();

    return 0;
}