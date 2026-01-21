#include "maths/functions.h"

#include <cmath>

namespace SDF{
    // Primitives
    double Line(double x, double y, double m = 1.0, double c = 0.0, double thickness = 0.05){
        double out =  y - m * x - c;
        return abs(out) - thickness;
    }
    double Circle(double x, double y, double r = 1.0){
        return x*x + y*y - r*r;
    }
    double Ellipse(double x, double y, double a = 1.0, double b = 1.0){
        return (x*x)/(a*a) + (y*y)/(b*b) - 1;
    }
    double Square(double x, double y, double r = 1.0){
        return std::max(abs(x), abs(y)) - r;
    }
    double Rectangle(double x, double y, double a = 1.0, double b = 1.0){
        return std::max(abs(x)/a, abs(y)/b) - 1;
    }
    double Heart(double x, double y, double r = 1.0, double a = 1.0, double b = 1.0){
        double xd = x/a;
        double yd = y/b;
        return pow(xd*xd + yd*yd - 1, 3) - r * xd*xd * pow(yd, 3);
    }
    double Hyperbola(double x, double y, double a = 1.0, double b = 1.0){
        return (x*x)/(a*a) - (y*y)/(b*b) - 1;
    }
    double Astroid(double x, double y, double a = 1.0, double b = 1.0){
        return pow(pow(x/a, 2.0), 1.0/3.0) +
                pow(pow(y/b, 2.0), 1.0/3.0) - 1;

    }
    double LuckyLeaf(double x, double y, double r = 1.0){
            return pow(x*x + y*y, 5) - r*r * pow(x*x - y*y, 2);
    }

    // Operations
    double Union(double d1, double d2){
        return std::min(d1, d2);
    }
    double Intersection(double d1, double d2){
        return std::max(d1, d2);
    }
    double Subtraction(double d1, double d2){
        return std::max(d1, -d2);
    }
    double Xor(double d1, double d2){
        return std::max(d1, d2) - std::min(d1, d2);
    }

    // Smooth Operations
    double Inversion(double d){
        return -d;
    }
    double Blend(double d1, double d2, double k){
        return (d1 * exp(-k * d1) + d2 * exp(-k * d2)) / (exp(-k * d1) + exp(-k * d2));
    }
    double SmoothUnion(double d1, double d2, double k){
        double h = std::max(k - abs(d1 - d2), 0.0) / k;
        return std::min(d1, d2) - h * h * h * k / 6.0;
    }
    double SmoothIntersection(double d1, double d2, double k){
        double h = std::max(k - abs(d1 - d2), 0.0) / k;
        return std::max(d1, d2) + h * h * h * k / 6.0;
    }
    double SmoothSubtraction(double d1, double d2, double k){
        double h = std::max(k - abs(d1 + d2), 0.0) / k;
        return std::max(d1, -d2) + h * h * h * k / 6.0;
    }
}