#include <bits/stdc++.h>
#include <ctime>
#include <windows.h>
using namespace std;

const double x_Step = 0.03;
const double y_Step = 0.075;

class Functions {
    public:
    class Line {
    public:
        static double value(double x, double y, double m = 1.0, double c = 0.0, double thickness = 0.05) {
            double out =  y - m * x - c;
            return abs(out) - thickness;
        }
    };

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

    class Rectangle {
    public:
        static double value(double x, double y, double a = 1.0, double b = 1.0) {
            return max(abs(x)/a, abs(y)/b) - 1;
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

class Draw{
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

        for(double x = -boundary; x <= boundary + x_Step; x += x_Step) {
            cout << "=";
        }
        cout << "=\n";
        for (double y = boundary; y >= -boundary; y -= y_Step) {
            cout << "|";
            for (double x = -boundary; x <= boundary; x += x_Step) {

                auto transformed = Transform(x, y, center.first, center.second);
                auto rotated = Rotation(transformed.first, transformed.second, angle, s);
                cout << shade(
                    ShapeType::value(rotated.first, rotated.second, arg...)
                );

            }
            cout << "|\n";
        }
        for(double x = -boundary; x <= boundary + x_Step; x += x_Step) {
            cout << "=";
        }
        cout << "=\n";

        printf("Center: (%.2f, %.2f) Angle: %.2f\n", center.first, center.second, angle);
    }
  
    static void drawFunc(function<double(double, double)> func, pair<double, double> center = {0.0 ,0.0}, double angle = 0.0, RotationType s = deg) {
        ResetCursor();

        for(double x = -boundary; x <= boundary + x_Step; x += x_Step) {
            cout << "=";
        }
        cout << "=\n";
        for (double y = boundary; y >= -boundary; y -= y_Step) {
            cout << "|";
            for (double x = -boundary; x <= boundary; x += x_Step) {

                auto transformed = Transform(x, y, center.first, center.second);
                auto rotated = Rotation(transformed.first, transformed.second, angle, s);
                cout << shade(
                    func(rotated.first, rotated.second)
                );

            }
            cout << "|\n";
        }
        for(double x = -boundary; x <= boundary + x_Step; x += x_Step) {
            cout << "=";
        }
        cout << "=\n";

        printf("Center: (%.2f, %.2f) Angle: %.2f\n", center.first, center.second, angle);
    }  



    static vector<vector<double>> getValueMap(
        const function<double(double, double)>& func,
        pair<double, double> center = {0.0, 0.0},
        double angle = 0.0,
        RotationType s = deg
    ) {
        vector<vector<double>> valueMap;

        int rows = static_cast<int>((2 * boundary) / y_Step) + 1;
        int cols = static_cast<int>((2 * boundary) / x_Step) + 1;

        valueMap.reserve(rows);

        for (double y = boundary; y >= -boundary; y -= y_Step) {
            vector<double> row;
            row.reserve(cols);

            for (double x = -boundary; x <= boundary; x += x_Step) {
                auto t = Transform(x, y, center.first, center.second);
                auto r = Rotation(t.first, t.second, angle, s);
                row.push_back(func(r.first, r.second));
            }
            valueMap.push_back(std::move(row));
        }
        return valueMap;
    }


    static vector<vector<double>> MergeValues(
        const vector<vector<double>>& vals1,
        const vector<vector<double>>& vals2,
        const function<double(double, double)>& mergeFunc =
            [](double a, double b) { return min(a, b); }
    ) {
        int rows = vals1.size();
        int cols = vals1[0].size();

        vector<vector<double>> merged(rows, vector<double>(cols));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                merged[i][j] = mergeFunc(vals1[i][j], vals2[i][j]);
            }
        }
        return merged;
    }


    static void drawByValue(const vector<vector<double>>& values) {
        ResetCursor();

        int rows = values.size();
        int cols = values[0].size();
    
        cout << "+";
        for (int j = 0; j < cols; j++) cout << "-";
        cout << "+\n";

        for (int i = 0; i < rows; i++) {
            cout << "|";
            for (int j = 0; j < cols; j++) {
                cout << shade(values[i][j]);
            }
            cout << "|\n";
        }

        cout << "+";
        for (int j = 0; j < cols; j++) cout << "-";
        cout << "+\n";
    }



    class FunAnimation {
        public:

        static void HeartPopPop(){
            SetBoundary(1.5);
            RemoveCursor();
            double size = 0.7;
            bool up = true;
            while(true){
                Draw::drawFunc([&](double x, double y) { 
                    return Functions::Heart::value(x, y, 1, size, size); 
                });
                if(up) size += 0.05;
                else size -= 0.05;
                if(size > 1) up = false;
                if(size < 0.7) up = true;
            }
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
    Draw::SetBoundary(1.5);
    Draw::RemoveCursor();

    Player player;
    double x0 = 0.0, y0 = 0.0;
    double angle = 0.0;
    double size = 0.7;
    bool up = true;

    // while(true){
    //     Draw::draw<Functions::Heart>({x0,y0}, angle, Draw::deg, 1.0, 0.5, 0.5);
    //     angle += 10.0;
    //     if(angle > 360.0) angle -= 360.0;
    //         x0 += 0.1;
    //         y0 += 0.1;
    //     }
    //     else{
    //         x0 -= 0.1;
    //         y0 -= 0.1;
    //     }

    //     if(x0 > 1.2) up = false;
    //     if(x0 < -1.2) up = true;
    //     Sleep(10);
    // }

    // while(true){
    //     player.Control();
    //     auto pos = player.getPosition(); 
    //     double angle = player.getAngle();
    // }

    // Draw::FunAnimation::HeartPopPop();

    while(true){
        player.Control();
        auto pos = player.getPosition(); 
        double angle = player.getAngle();

        Draw::drawByValue(
            Draw::MergeValues(
                Draw::getValueMap(
                    [](double x, double y) {
                        return Functions::Circle::value(x, y, 0.5);
                    },
                    pos,
                    angle,
                    Draw::deg
                ),
                Draw::MergeValues(
                   Draw::getValueMap(
                        [](double x, double y) {
                            return Functions::Square::value(x, y, 0.4);
                        },
                        {1,1},
                        0.0,
                        Draw::deg
                    ),
                    Draw::getValueMap(
                        [](double x, double y) {
                            return Functions::Square::value(x, y ,0.4);
                        },
                        {-1,0.5},
                        0.0,
                        Draw::deg
                    )
                )
            )
        );
    }  
        return 0;
}