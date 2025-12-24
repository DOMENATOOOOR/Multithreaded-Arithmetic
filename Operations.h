#pragma once
#include <memory>
#include <string>
#include <stdexcept>

class Operations {
public:
    virtual ~Operations() = default;
    virtual double execute() const = 0;

    static std::unique_ptr<Operations> create(const std::string& cmd, double a, double b);
};

//=====================================//
// Операции //
class AddOperation : public Operations {
    double a, b;
public:
    AddOperation(double a, double b) : a(a), b(b) {}
    double execute() const override { return a + b; }
};

class SubtractOperation : public Operations {
    double a, b;
public:
    SubtractOperation(double a, double b) : a(a), b(b) {}
    double execute() const override { return a - b; }
};

class MultiplyOperation : public Operations {
    double a, b;
public:
    MultiplyOperation(double a, double b) : a(a), b(b) {}
    double execute() const override { return a * b; }
};

class DivideOperation : public Operations {
    double a, b;
public:
    DivideOperation(double a, double b) : a(a), b(b) {}
    double execute() const override {
        if (b == 0) throw std::runtime_error("Divide by zero");
        return a / b;
    }
};

class SquareAddOperation : public Operations {
    double a, b;
public:
    SquareAddOperation(double a, double b) : a(a), b(b) {}
    double execute() const override { return (a + b) * (a + b); }
};

class AddSquaresOperation : public Operations {
    double a, b;
public:
    AddSquaresOperation(double a, double b) : a(a), b(b) {}
    double execute() const override { return a * a + b * b; }
};
