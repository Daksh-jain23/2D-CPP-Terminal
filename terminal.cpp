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

    static char shade(double val) {
        return (val <= 0.0) ? '*' : ' ';
    }

    static void RemoveCursor() {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = FALSE;
        SetConsoleCursorInfo(consoleHandle, &info);
    }

    static void ResetCursor() {
        COORD pos = {0, 0};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }

    static pair<double, double> Transform(double x, double y, double tx, double ty) {
        return {x -tx, y - ty};
    }
    
    enum RotationType { deg, rad };
    static pair<double, double> Rotation(double x, double y, double angle, RotationType s = deg) {
        if (s == deg) angle = angle * M_PI / 180.0;

        double x_new = x * cos(angle) - y * sin(angle);
        double y_new = x * sin(angle) + y * cos(angle);
        return {x_new, y_new};
    }

    template<class ShapeType, typename... Args>
    static void draw(pair<double, double> center, double angle, RotationType s = deg, Args... arg) {

        ResetCursor();
        for(double x = -boundary; x <= boundary + 0.03; x += 0.03) {
            cout << "=";
        }
        cout << "=\n";
        for (double y = boundary; y >= -boundary; y -= 0.075) {
            cout << "|";
            for (double x = -boundary; x <= boundary; x += 0.03) {

                auto transformed = Transform(x, y, center.first, center.second);
                auto rotated = Rotation(transformed.first, transformed.second, angle, s);
                cout << shade(
                    ShapeType::value(rotated.first, rotated.second, arg...)
                );

            }
            cout << "|\n";
        }
        for(double x = -boundary; x <= boundary + 0.03; x += 0.03) {
            cout << "=";
        }
        cout << "=\n";

        printf("Center: (%.2f, %.2f) Angle: %.2f\n", center.first, center.second, angle);
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

class Player {
    double x, y;
    double angle;
public:
    Player() : x(0.0), y(0.0), angle(0.0) {}

    void move(double dx, double dy) {
        x += dx;
        y += dy;
    }

    void rotate(double dAngle) {
        angle += dAngle;
    }

    pair<double, double> getPosition() const {
        return {x, y};
    }

    double getAngle() const {
        return angle;
    }

    void Control() {
        if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) {
            x -= 0.1;
        }
        if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) {
            x += 0.1;
        }
        if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) {
            y += 0.1;
        }
        if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) {
            y -= 0.1;
        }
        if (GetAsyncKeyState('Q')) {
            angle -= 5.0;
            if(angle < 0.0) angle += 360.0;
        }
        if (GetAsyncKeyState('E')) {
            angle += 5.0;
            if(angle >= 360.0) angle -= 360.0;
        }
    }
};


int main() {
    Shape::SetBoundary(1.5);
    Shape::RemoveCursor();

    // double x0 = 0.0, y0 = 0.0;
    // double angle = 0.0;
    // bool up = true;

    // while(true){
    //     Shape::draw<Shape::Heart>({x0,y0}, angle, Shape::deg, 1.0, 0.5, 0.5);
    //     angle += 10.0;
    //     if(angle > 360.0) angle -= 360.0;
    //     if(up){
    //         x0 += 0.1;
    //         y0 += 0.1;
    //     }
    //     else{
    //         x0 -= 0.1;
    //         y0 -= 0.1;
    //     }

    //     if(x0 > 1.2) up = false;
    //     if(x0 < -1.2) up = true;
    //     Sleep(100);
    // }

    Player player;
    while(true){
        player.Control();
        auto pos = player.getPosition();
        double angle = player.getAngle();
        Shape::draw<Shape::Square>(pos, angle, Shape::deg, 0.5);
    }

    return 0;
}