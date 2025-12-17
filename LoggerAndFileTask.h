#pragma once
#include <exception>
#include <fstream>
#include <future>
#include <iostream>
#include <mutex>
#include <vector>

class Logger {
    std::ofstream LogFile;
    std::string filepath;

public:

    Logger(const std::string& path): filepath(path) {
        try {
            LogFile.open(filepath, std::ios::out | std::ios::app);
        }
        catch(...) {
            std::throw_with_nested(std::runtime_error("Logger could not open: " + filepath));
        }
    }

    ~Logger() {
        LogFile.close();
    }

    std::mutex mforlog;
    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mforlog);
        LogFile << message << std::endl;
    }
};



class Operation {
    std::string cmd;
    double a{};
    double b{};
public:
    Operation (std::string& cmd, double a, double b): cmd(cmd), a(a), b(b) {}
    double execute() const {
        if (cmd == "add") return a + b;
        if (cmd == "sub") return a - b;
        if (cmd == "mult") return a * b;
        if (cmd == "sq_add") return (a + b)*(a + b);
        if (cmd == "add_sq") return a * a + b * b;
        if (cmd == "div") {
            if (b == 0) throw std::runtime_error("Divide by zero");
            return a / b;
        }
        throw std::runtime_error("Unknown command: " + cmd);
    }
};

class FileTask {
    std::filesystem::path file;
    Logger& logger;
    public:
    FileTask(const std::filesystem::path& f, Logger& log): file(f), logger(log) {}

    double operator()() const {
        std::ifstream in(file);
        if (!in.is_open()) {
            logger.log("File" + file.string() + " could not be opened");
            return 0.0;
        }

        std::string cmd;
        double a, b;
        in >> cmd >> a >> b;
        try {
            Operation op(cmd, a, b);
            double result = op.execute();
            logger.log("Processed: " + file.string() + "Result: " + std::to_string(result));
            return result;
        }
        catch(const std::exception& e) {
            logger.log("Error in: " + file.string() + ": " + e.what());
            return 0.0;
        }
    }
};