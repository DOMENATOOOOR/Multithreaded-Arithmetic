#include <exception>
#include <fstream>
#include <future>
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>

static double total_sum = 0;
std::mutex mforsum;
std::mutex mforfiles;

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



double compute(const std::string& cmd, double a, double b) {
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

void mainblock(std::queue<std::filesystem::path>& files, Logger& logger) {
    while(true) {
        std::filesystem::path file;

        {
            std::lock_guard<std::mutex> lock(mforfiles);
            if (files.empty()) return;
            file = files.front();
            files.pop();
        }

        std::ifstream in(file);
        if (!in.is_open()) {
            logger.log("File could not be opened " + file.string());
            continue;
        }

        std::string line;
        std::getline(in, line);
        in.close();

        std::istringstream iss(line);
        double a, b;
        std::string cmd;
        iss >> cmd >> a >> b;

        double result = 0.0;
        try {
            result = compute(cmd, a, b);
        }
        catch(std::exception& e) {
            logger.log(e.what());
            continue;
        }

        {
            std::lock_guard<std::mutex> lock(mforsum);
            total_sum += result;
        }

        logger.log("Processed " + file.string() + " result = " + std::to_string(result));

    }
}

int main() {
    Logger Logger("LoggerOfArithmetic.txt");

    std::string input_dir = "/Users/mac_aleksandr/data";
    std::string output_file = "OutputOfArithmetic.txt";

    std::queue<std::filesystem::path> files;
    for (auto& p : std::filesystem::directory_iterator(input_dir)) {
        if(p.path().filename().string().find("in_") == 0 && p.path().extension() == ".txt")
            files.push(p.path());
    }



    unsigned int n_threads = std::thread::hardware_concurrency();
    std::cout << "Number of hardware threads: " << n_threads << std::endl;

    std::vector<std::thread> threads;
    for (int i = 0; i < n_threads; ++i) {
        threads.emplace_back(&mainblock, std::ref(files), std::ref(Logger));
    }

    for (auto& t : threads) {
        t.join();
    }

    std::ofstream out(output_file);
    out << total_sum << std::endl;
    out.close();

    Logger.log("Total sum in file: " + output_file);

    return 0;
}
