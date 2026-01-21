#include "maths/functions.h"

#include <cmath>

namespace SDF{
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
}