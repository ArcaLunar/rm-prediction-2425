#define SPDLOG_ACTIVE_LEVEL SPDLOG_LOGGER_TRACE // 设置为输出文件名和行号

#include <spdlog/spdlog.h>
#include "Calibration.hpp"

int main() {
    spdlog::set_pattern("[%H:%M:%S.%e] [%l] [%s %!:%#]  %v");
    spdlog::flush_every(std::chrono::seconds(1)); // 初始化日志

    SPDLOG_INFO("main.cpp start working.");

    return 0;
}