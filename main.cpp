#include <iostream>
#include <regex>

class Rational {
private:
    int x_, y_;

public:
    void normalize() {
        int gcd = std::__gcd(abs(x_), abs(y_));
        x_ /= gcd * (y_ < 0 ? -1 : 1);
        y_ = abs(y_ / gcd);
    }

    Rational(int x = 0, int y = 1) : x_(x), y_(y) { normalize(); }

    int numerator() const { return x_; }
    int denominator() const { return y_; }

    Rational& operator=(const Rational& other);

    Rational operator+();
    Rational operator-();

    Rational operator+(const Rational& other);
    Rational operator+(const int num);
    friend Rational operator+(const int num, const Rational& other);

    Rational operator-(const Rational& other);
    Rational operator-(const int num);
    friend Rational operator-(const int num, const Rational& other);

    Rational operator*(const Rational& other);
    Rational operator*(const int num);
    friend Rational operator*(const int num, const Rational& other);

    Rational operator/(const Rational& other);
    Rational operator/(const int num);
    friend Rational operator/(const int num, const Rational& other);

    Rational operator+=(const Rational& other);
    Rational operator-=(const Rational& other);
    Rational operator*=(const Rational& other);
    Rational operator/=(const Rational& other);

    bool operator==(const Rational& other);
    bool operator!=(const Rational& other);

    Rational& operator++();
    Rational operator++(int);

    Rational& operator--();
    Rational operator--(int);
};

Rational& Rational::operator=(const Rational& other) {
    x_ = other.x_;
    y_ = other.y_;
    normalize();
    return *this;
}

Rational Rational::operator+() {
    return *this;
}

Rational Rational::operator-() {
    return {-x_, y_};
}

Rational Rational::operator+(const Rational& other) {
    int lcm = abs(y_) * abs(other.y_) / std::__gcd(abs(y_), abs(other.y_));
    normalize();
    return {x_ * lcm / y_ + other.x_ * (lcm / other.y_), lcm};
}

Rational Rational::operator-(const Rational &other) {
    int lcm = abs(y_) * abs(other.y_) / std::__gcd(abs(y_), abs(other.y_));
    normalize();
    return {x_ * lcm / y_ - other.x_ * (lcm / other.y_), lcm};
}

Rational Rational::operator*(const Rational &other) {
    return {x_ * other.x_, y_ * other.y_};
}

Rational Rational::operator/(const Rational &other) {
    return {x_ * other.y_, y_ * other.x_};
}

Rational Rational::operator+=(const Rational &other) {
    int lcm = abs(y_) * abs(other.y_) / std::__gcd(abs(y_), abs(other.y_));
    x_ *= lcm / y_;
    x_ += other.x_ * (lcm / other.y_);
    y_ = lcm;
    normalize();
    return *this;
}

Rational Rational::operator-=(const Rational &other) {
    int lcm = abs(y_) * abs(other.y_) / std::__gcd(abs(y_), abs(other.y_));
    x_ *= lcm / y_;
    x_ -= other.x_ * (lcm / other.y_);
    y_ = lcm;
    normalize();
    return *this;
}

Rational Rational::operator*=(const Rational &other) {
    x_ *= other.x_;
    y_ *= other.y_;
    normalize();
    return *this;
}

Rational Rational::operator/=(const Rational &other) {
    x_ *= other.y_;
    y_ *= other.x_;
    normalize();
    return *this;
}

bool Rational::operator==(const Rational &other) {
    int firstGcd = std::__gcd(x_, y_), secondGcd = std::__gcd(other.x_, other.y_);
    return (x_ / firstGcd == other.x_ / secondGcd && y_ / firstGcd == other.y_ / secondGcd);
}

bool Rational::operator!=(const Rational &other) {
    int firstGcd = std::__gcd(x_, y_), secondGcd = std::__gcd(other.x_, other.y_);
    return (x_ / firstGcd != other.x_ / secondGcd || y_ / firstGcd != other.y_ / secondGcd);
}

Rational& Rational::operator++() {
    x_ += y_;
    normalize();
    return *this;
}

Rational Rational::operator++(int) {
    Rational tmp(x_, y_);
    x_ += y_;
    normalize();
    return tmp;
}

Rational& Rational::operator--() {
    x_ -= y_;
    normalize();
    return *this;
}

Rational Rational::operator--(int) {
    Rational tmp(x_, y_);
    x_ -= y_;
    normalize();
    return tmp;
}

Rational Rational::operator+(const int num) {
    return {x_ + y_ * num, y_};
}

Rational operator+(const int num, const Rational& other) {
    return {other.x_ + other.y_ * num, other.y_};
}

Rational Rational::operator-(const int num) {
    return {x_ - y_ * num, y_};
}

Rational operator-(const int num, const Rational &other) {
    return {other.x_ - other.y_ * num, other.y_};
}

Rational Rational::operator*(const int num) {
    return {x_ * num, y_};
}

Rational operator*(const int num, const Rational &other) {
    return {other.x_ * num, other.y_};
}

Rational Rational::operator/(const int num) {
    return {x_, y_ * num};
}

Rational operator/(const int num, const Rational &other) {
    return {other.x_, other.y_ * num};
}
