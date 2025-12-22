#include "Logger.h"

Logger::Logger(const std::string& path) : filepath(path) {
    try {
        LogFile.open(filepath, std::ios::out | std::ios::app);
    } catch (...) {
        std::throw_with_nested(std::runtime_error("Logger could not open: " + filepath));
    }
}

Logger::~Logger() {
    if (LogFile.is_open()) LogFile.close();
}

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(mforlog);
    LogFile << message << std::endl;
}
