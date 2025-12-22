#pragma once
#include "Logger.h"
#include "Operation.h"
#include <filesystem>

class FileTask {
public:
    FileTask(const std::filesystem::path& f, Logger& log);
    double operator()() const;

private:
    std::filesystem::path file;
    Logger& logger;
};
