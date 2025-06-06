#pragma once
#include <cmath>
#include "rational.h"

template<class Number>
Number IntegerPow(Number l_op, Number r_op) {
    Number res = 1;
    while (r_op > 0) {
        if (r_op & 1) {
            res *= l_op;
        }
        r_op >>= 1;
        l_op *= l_op;
    }
    return res;
}

inline Rational Pow(Rational lhs, Rational rhs) {
    if (rhs.GetDenominator() != 1) {
        std::abort();
    }
    auto pow = rhs.GetNumerator();
    if (pow >= 0) {
        return {IntegerPow(lhs.GetNumerator(), pow), IntegerPow(lhs.GetDenominator(), pow)};
    } else {
        return {IntegerPow(lhs.GetDenominator(), -pow), IntegerPow(lhs.GetNumerator(), -pow)};
    }
}

template<typename Number>
Number Pow(const Number& base, const Number& exponent) {
    if constexpr (std::is_floating_point_v<Number>) {
        return std::pow(base, exponent);
    } else if constexpr (std::is_integral_v<Number>) {
        return IntegerPow(base, exponent);
    } else if constexpr (std::is_same_v<Number, Rational>) {
        return Pow(base, exponent);
    }
    return base;
}





