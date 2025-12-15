#include <bits/stdc++.h>
#include <ctime>
#include <windows.h>
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

    static pair<double, double> Rotation(double x, double y, double angle) {
        double x_new = x * cos(angle) - y * sin(angle);
        double y_new = x * sin(angle) + y * cos(angle);
        return {x_new, y_new};
    }

    template<class ShapeType, typename... Args>
    static void draw(double angle, Args... arg) {
        for(double x = -boundary; x <= boundary + 0.03; x += 0.03) {
            cout << "=";
        }
        cout << "=\n";

        for (double y = boundary; y >= -boundary; y -= 0.075) {
            cout << "|";
            for (double x = -boundary; x <= boundary; x += 0.03) {

                auto [xr, yr] = Rotation(x, y, angle);
                cout << Shade( ShapeType::value(xr, yr, arg...) );

            }
            cout << "|\n";
        }

        for(double x = -boundary; x <= boundary + 0.03; x += 0.03) {
            cout << "=";
        }
        cout << "=\n";
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
    Shape::SetBoundary(1.5);
    double angle = 0.0;
    while(true){
        system("cls");
        Shape::draw<Shape::Heart>(angle, 1.0, 0.7, 0.7);
        angle += 0.1;
    }
    return 0;
}