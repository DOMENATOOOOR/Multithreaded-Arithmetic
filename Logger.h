#pragma once
#include <fstream>
#include <mutex>
#include <string>
#include <exception>

class Logger {
public:
    Logger(const std::string& path);
    ~Logger();
    void log(const std::string& message);

private:
    std::ofstream LogFile;
    std::string filepath;
    std::mutex mforlog;
};
