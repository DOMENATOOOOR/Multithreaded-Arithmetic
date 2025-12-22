#include "TaskProcessor.h"
#include "FileTask.h"
#include <filesystem>
#include <future>
#include <fstream>
#include <vector>

double processFiles(const std::string& input_dir, const std::string& output_file, Logger& logger) {
    std::vector<std::future<double>> futures;

    for (const auto& p : std::filesystem::directory_iterator(input_dir)) {
        if (p.path().filename().string().starts_with("in_")) {
            FileTask task(p.path(), logger);
            futures.push_back(std::async(std::launch::async, task));
        }
    }

    double total_sum = 0.0;
    for (auto& f : futures) {
        total_sum += f.get();
    }

    std::ofstream out(output_file, std::ios::out | std::ios::app);
    out << total_sum << std::endl;
    out.close();

    logger.log("Total sum in file: " + output_file + "\nDone!\n");
    return total_sum;
}
