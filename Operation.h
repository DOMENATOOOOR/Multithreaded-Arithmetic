#pragma once
#include <string>
#include <stdexcept>

class Operation {
public:
    Operation(const std::string& cmd, double a, double b);
    double execute() const;

private:
    std::string cmd;
    double a{};
    double b{};
};
