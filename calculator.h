
#pragma once

#include <string>
#include <optional>
#include "rational.h"
#include "pow.h"

using Error = std::string;

// Реализация шаблонного калькулятора.
template <typename Number>
class Calculator {

public:
    // Заменяет текущее число (результат) на число n
    void Set(Number n) {
        number_ = n;
    }

    // Возвращает текущий результат вычислений калькулятора. В только что
    // сконструированном калькуляторе этот метод возвращает 0
    Number GetNumber() const {
        return number_;
    }

    // Прибавляет число n к текущему результату внутри калькулятора.
    std::optional<Error> Add(Number n) {
        number_ += n;
        return std::nullopt;
    }

    // Вычитает число n из текущего результата.
    std::optional<Error> Sub(Number n) {
        number_ -= n;
        return std::nullopt;
    }

    // Делит текущий результат на n.
    std::optional<Error> Div(Number n) {
        if constexpr (!std::is_floating_point_v<Number>) {
            if (n == 0) {
                return std::optional<Error>{"Division by zero"};
            }
        }

        number_ /= n;
        return std::nullopt;
    }

    // Умножает текущий результат на n.
    std::optional<Error> Mul(Number n) {
        number_ *= n;
        return std::nullopt;
    }

    // Возводит текущий результат в степень n.
    std::optional<Error> Pow(Number n) {
        if constexpr (!std::is_floating_point_v<Number>) {
            if (n == 0 && number_ == 0) {
                return std::optional<Error>{"Zero power to zero"};
            }
        }
        if constexpr (std::is_same_v<Number, Rational>) {
            if (n.GetDenominator() != 1) {
                return std::optional<Error>{"Fractional power is not supported"};
            }
        }
        if constexpr (std::is_integral_v<Number>) {
            if (n < 0) {
                return std::optional<Error>{"Integer negative power"};
            }
        }

        number_ = ::Pow(number_, n);
        return std::nullopt;
    }

    // Сохраняет текущий результат в ячейку памяти калькулятора.
    void Save() {
        saving_number_ = number_;
    }

    // Загружает число из памяти калькулятора в текущий результат.
    void Load() {
        number_ = saving_number_.value();
    }

    // Возвращает true, если ячейка памяти непустая.
    bool GetHasMem() const {
        return saving_number_.has_value();
    }

private:
    Number number_ = 0;
    std::optional<Number> saving_number_;
};
