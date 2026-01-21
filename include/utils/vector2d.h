#pragma once
#include <iostream>

struct Vec2 {
    double x, y;

    Vec2();
    Vec2(double x_, double y_);

    Vec2 operator+(const Vec2& o) const;    // vector addition 
    Vec2 operator-(const Vec2& o) const;    // vector subtraction
    Vec2 operator*(double s) const;         // const mul
    Vec2& operator+=(const Vec2& o);       // self add
    
    
    friend std::ostream& operator<<(std::ostream& out, const Vec2& v); // print
    
    double dot(const Vec2& o) const;       // dot product
    double mag() const;                 // magnitude
};

