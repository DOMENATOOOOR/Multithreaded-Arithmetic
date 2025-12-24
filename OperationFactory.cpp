#include "Operations.h"


std::unique_ptr<Operations> Operations::create(const std::string& cmd, double a, double b) {
    if (cmd == "add") return std::make_unique<AddOperation>(a, b);
    if (cmd == "sub") return std::make_unique<SubtractOperation>(a, b);
    if (cmd == "mult") return std::make_unique<MultiplyOperation>(a, b);
    if (cmd == "div") return std::make_unique<DivideOperation>(a, b);
    if (cmd == "sq_add") return std::make_unique<SquareAddOperation>(a, b);
    if (cmd == "add_sq") return std::make_unique<AddSquaresOperation>(a, b);

    throw std::runtime_error("Unknown command: " + cmd);
}
