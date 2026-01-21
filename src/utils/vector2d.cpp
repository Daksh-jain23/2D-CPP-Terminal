#include "utils/vector2d.h"
#include <cmath>

Vec2::Vec2() {
    x = y = 0.0;
}

Vec2::Vec2(double x_, double y_) : x(x_), y(y_) {}

Vec2 Vec2::operator+(const Vec2& o) const {
    return {x + o.x, y + o.y};
}

Vec2 Vec2::operator-(const Vec2& o) const {
    return {x - o.x, y - o.y};
}

Vec2 Vec2::operator*(double s) const {
    return {x * s, y * s};
}

Vec2& Vec2::operator+=(const Vec2& o) {
    x += o.x;
    y += o.y;
    return *this;
}

double Vec2::dot(const Vec2& o) const {
    return x * o.x + y * o.y;
}

double Vec2::mag() const{
    return std::sqrt(x * x + y * y);
}

std::ostream& operator<<(std::ostream& out, const Vec2& v) {
    out << v.x << ", " << v.y;
    return out;
}

