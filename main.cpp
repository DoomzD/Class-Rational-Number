#include <iostream>
#include <regex>

class Rational {
private:
    int x_, y_;

public:
    Rational(int x = 0, int y = 1) : x_(x), y_(y) { }

    int numerator() { return x_ / std::__gcd(abs(x_), abs(y_)) * (y_ < 0 ? -1 : 1); }
    int denominator() { return abs(y_) / std::__gcd(abs(x_), abs(y_)); }

    Rational& operator=(const Rational& other);
    Rational& operator+();
    Rational operator-();

    Rational operator+(const Rational& other);
    Rational operator-(const Rational& other);
    Rational operator*(const Rational& other);
    Rational operator/(const Rational& other);

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
    return *this;
}

Rational& Rational::operator+() {
    return *this;
}

Rational Rational::operator-() {
    return {-((*this).x_), y_};
}

Rational Rational::operator+(const Rational& other) {
    int lcm = x_ * y_ / std::__gcd(y_, other.y_);
    return {x_ * lcm / y_ + other.x_ * (lcm / other.y_), lcm};
}

Rational Rational::operator-(const Rational &other) {
    int lcm = x_ * y_ / std::__gcd(y_, other.y_);
    return {x_ * lcm / y_ - other.x_ * (lcm / other.y_), lcm};
}

Rational Rational::operator*(const Rational &other) {
    return {x_ * other.x_, y_ * other.y_};
}

Rational Rational::operator/(const Rational &other) {
    return {x_ * other.y_, y_ * other.x_};
}

Rational Rational::operator+=(const Rational &other) {
    int lcm = y_ * other.y_ / std::__gcd(y_, other.y_);
    x_ *= lcm / y_;
    x_ += other.x_ * (lcm / other.y_);
    y_ = lcm;
    return *this;
}

Rational Rational::operator-=(const Rational &other) {
    int lcm = x_ * y_ / std::__gcd(y_, other.y_);
    x_ *= lcm / y_;
    x_ -= other.x_ * (lcm / other.y_);
    y_ = lcm;
    return *this;
}

Rational Rational::operator*=(const Rational &other) {
    x_ *= other.x_;
    y_ *= other.y_;
    return *this;
}

Rational Rational::operator/=(const Rational &other) {
    x_ *= other.y_;
    y_ *= other.x_;
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
    return *this;
}

Rational Rational::operator++(int) {
    Rational tmp(x_, y_);
    x_ += y_;
    return tmp;
}

Rational& Rational::operator--() {
    x_ -= y_;
    return *this;
}

Rational Rational::operator--(int) {
    Rational tmp(x_, y_);
    x_ -= y_;
    return tmp;
}

int main() {
    Rational r(10, 5), q(15, 2);
    r = ++r + q;
    std::cout << r.numerator() << " " << r.denominator() << '\n' << q.numerator() << " " <<
              q.denominator() << '\n';
}
