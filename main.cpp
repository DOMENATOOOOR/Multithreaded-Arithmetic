#include "Logger.h"
#include "TaskProcessor.h"
#include <string>

int main() {
    Logger logger("LoggerOfArithmetic.txt");

    std::string input_dir = "/Users/mac_aleksandr/data";
    std::string output_file = "OutputOfArithmetic.txt";

    processFiles(input_dir, output_file, logger);

    return 0;
}
