#pragma once

#include <cstdlib>
#include <numeric>
#include <cstdint>
#include <iostream>

class Rational {
public:
    Rational() = default;
    Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {
        if (denominator_ == 0) {
            std::abort();
        }
        Reduction();
    }
    Rational(int numerator) : numerator_(numerator), denominator_(1) {}
    Rational(const Rational& r) : numerator_(r.numerator_), denominator_(r.denominator_) {}

    int GetNumerator() const {
        return numerator_;
    }

    int GetDenominator() const {
        return denominator_;
    }

    Rational Inv() const {
        return Rational(denominator_, numerator_);
    }

    // Присваивание
    Rational& operator=(const Rational& r) {
        numerator_ = r.numerator_;
        denominator_ = r.denominator_;
        return *this;
    }

    // Присваивающие арифметические
    Rational& operator*=(const Rational& other) {
        numerator_ *= other.numerator_;
        denominator_ *= other.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator/=(const Rational &other) {
        numerator_ *= other.denominator_;
        denominator_ *= other.numerator_;
        Reduction();
        return *this;
    }

    Rational& operator+=(const Rational &other) {
        numerator_ = numerator_ * other.denominator_ + denominator_ * other.numerator_;
        denominator_ *= other.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator-=(const Rational &other) {
        numerator_ = numerator_ * other.denominator_ - denominator_ * other.numerator_;
        denominator_ *= other.denominator_;
        Reduction();
        return *this;
    }
    // Перегрузка приведения
    explicit operator double() const {
        double res = static_cast<double> (numerator_) / denominator_;
        return res;
    }

    // Перегрузка ввода из потока
    friend std::ostream& operator<<(std::ostream &os, const Rational &p) {
        auto rational = p;
        rational.Reduction();
        os << rational.numerator_;
        if (rational.denominator_ != 1) {
            os << " / " << rational.denominator_ ;
        }
        return os;
    }
    // Перегрузка вывода в поток
    friend std::istream& operator>>(std::istream& is, Rational &r) {
        int num;
        is >> std::ws; // пропускаем пробелы
        if (!(is >> num)) {
            // Не удалось прочитать число — ошибка
            return is;
        }
        if (is.eof()) {
            r.numerator_ = num;
            r.denominator_ = 1; // по умолчанию
            return is;
        }

        // Попытка прочитать символ-разделитель '/'
        char sep;
        is >> std::ws; // пропускаем пробелы перед разделителем
        if (!(is.get(sep))) {
            // Не удалось прочитать символ — значит знаменатель не указан
            r.numerator_ = num;
            r.denominator_ = 1; // по умолчанию
            return is;
        }

        if (sep != '/') {
            // Символ не '/', возвращаем его обратно в поток и считаем, что знаменатель не указан
            is.unget();
            r.numerator_ = num;
            r.denominator_ = 1;
            return is;
        }

        // Читаем знаменатель после '/'
        int den;
        is >> std::ws; // пропускаем пробелы перед знаменателем
        if (!(is >> den)) {
            // Не удалось прочитать знаменатель — ошибка
            is.setstate(std::ios::failbit);
            return is;
        }

        if (den == 0) {
            // Знаменатель равен нулю — ошибка
            is.setstate(std::ios::failbit);
            return is;
        }

        r.numerator_ = num;
        r.denominator_ = den;

        return is;
    }
    // Унарные
    Rational operator+() const{
        return *this;
    }
    Rational operator-() const {
        return Rational(-numerator_, denominator_);
    }

private:
    // Метод для приведения дроби к корректной форме.
    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

private:
    int numerator_ = 0;
    int denominator_ = 1;
};

// Проверки на равенство и трёхстороннего сравнения
inline auto operator<=>(const Rational& r1, const Rational& r2) {
    std::int64_t num = static_cast<std::int64_t>(r1.GetNumerator()) * r2.GetDenominator();
    std::int64_t dev = static_cast<std::int64_t>(r1.GetDenominator()) * r2.GetNumerator();
    return num <=> dev;
}

inline bool operator==(const Rational& r1, const Rational& r2) {
    std::int64_t num = static_cast<std::int64_t>(r1.GetNumerator()) * r2.GetDenominator();
    std::int64_t dev = static_cast<std::int64_t>(r1.GetDenominator()) * r2.GetNumerator();
    return num == dev;
}
// Бинарные арифметические
inline Rational operator+(Rational r1, Rational r2) {
    r1 += r2;
    return r1;
}

inline Rational operator-(Rational r1, Rational r2) {
    r1 -= r2;
    return r1;
}

inline Rational operator*(Rational r1, Rational r2) {
    r1 *= r2;
    return r1;
}

inline Rational operator/(Rational r1, Rational r2) {
    r1 /= r2;
    return r1;
}
