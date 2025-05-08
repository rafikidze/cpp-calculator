#include "calculator.h"
#include <cmath>

void Calculator::Set(Number n) {
    number_ = n;
}

Number Calculator::GetNumber() const {
    return number_;
}

void Calculator::Add(Number n) {
    number_ += n;
}

void Calculator::Sub(Number n) {
    number_ -= n;
}

void Calculator::Div(Number n) {
    number_ /= n;
}

void Calculator::Mul(Number n) {
    number_ *= n;
}

void Calculator::Pow(Number n) {
    number_ = std::pow(number_, n);
}

void Calculator::Save() {
    saving_number_ = number_;
    was_saving_ = true;
}

void Calculator::Load() {
    number_ = saving_number_;
}

bool Calculator::HasMem() const {
    return was_saving_;
}

std::string Calculator::GetNumberRepr() const {
    return std::to_string(number_);
}
