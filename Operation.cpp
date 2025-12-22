#include "Operation.h"

Operation::Operation(const std::string& cmd_, double a_, double b_)
    : cmd(cmd_), a(a_), b(b_) {}

double Operation::execute() const {
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
