#include "LoggerAndFileTask.h"

static double total_sum = 0.0;



int main() {
    Logger logger("LoggerOfArithmetic.txt");

    std::string input_dir = "/Users/mac_aleksandr/data";
    std::string output_file = "OutputOfArithmetic.txt";

    std::vector<std::future<double>> futures;
    for (const auto& p : std::filesystem::directory_iterator(input_dir)) {
        if(p.path().filename().string().starts_with("in_")) {
            FileTask task(p.path(), logger);
            futures.push_back(std::async(std::launch::async, task));
        }
    }

    for (auto& f : futures) {
        total_sum += f.get();
    }

    std::ofstream out(output_file, std::ios::out | std::ios::app);
    out << total_sum << std::endl;
    logger.log("Total sum in file: " + output_file + '\n' +  "Done!" + '\n' + '\n' );
    out.close();

    return 0;
}
