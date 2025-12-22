#include "FileTask.h"
#include <fstream>

FileTask::FileTask(const std::filesystem::path& f, Logger& log)
    : file(f), logger(log) {}

double FileTask::operator()() const {
    std::ifstream in(file);
    if (!in.is_open()) {
        logger.log("File " + file.string() + " could not be opened");
        return 0.0;
    }

    std::string cmd;
    double a, b;
    in >> cmd >> a >> b;

    try {
        Operation op(cmd, a, b);
        double result = op.execute();
        logger.log("Processed: " + file.string() + " Result: " + std::to_string(result));
        return result;
    } catch (const std::exception& e) {
        logger.log("Error in: " + file.string() + ": " + e.what());
        return 0.0;
    }
}
