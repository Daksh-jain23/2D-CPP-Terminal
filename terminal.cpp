#include <bits/stdc++.h>
using namespace std;

class Shape {
    inline static double boundary = 1.5;
    public:
    static void SetBoundary(double b) {
        boundary = b;
    }

    static char Shade(double val) {
        if(val <= 0.0) return '*';
        return ' ';                   
    }  

    template<class shapeType, typename... Args>
    static void draw(Args... arg) {
        for(double y = boundary;y >= -boundary;y-= 0.075){
            for(double x = -boundary;x <= boundary;x += 0.03){
                cout << Shade(shapeType::value(x,y, arg...));
            }
            cout << endl;
        }
    }

    class Circle {
    public:
        static double value(double x, double y, double r = 1.0) {
            return x*x + y*y - r*r;
        }

    };

    class Ellipse {
    public:
        static double value(double x, double y, double a = 1.0, double b = 1.0) {
            return (x*x)/(a*a) + (y*y)/(b*b) - 1;
        }

    };

    class Square {
    public:
        static double value(double x, double y, double r = 1.0) {
            return max(abs(x), abs(y)) - r;
        }

    };

    class Heart {
    public:
        static double value(double x, double y, double r = 1.0, double a = 1.0, double b = 1.0) {
            double xd = x/a;
            double yd = y/b;
            return pow(xd*xd + yd*yd - 1, 3) - r * xd*xd * pow(yd, 3);
        }

    };

    class Hyperbola {
    public:
        static double value(double x, double y, double a = 1.0, double b = 1.0) {
            return (x*x)/(a*a) - (y*y)/(b*b) - 1;
        }

    };

    class Astroid {
    public:
        static double value(double x, double y, double a = 1.0, double b = 1.0) {
            return pow(pow(x/a, 2.0), 1.0/3.0) +
                   pow(pow(y/b, 2.0), 1.0/3.0) - 1;
        }

    };

    class LuckyLeaf {
    public:
        static double value(double x, double y, double r = 1.0) {
            return pow(x*x + y*y, 5) - r*r * pow(x*x - y*y, 2);
        }

    };
};             


int main() {
    Shape::draw<Shape::Heart>(1.0, 0.5, 0.5);
    return 0;
}