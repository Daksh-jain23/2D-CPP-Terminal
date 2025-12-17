#include <windows.h>
#include <cmath>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <functional>
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

class CursorController {
    inline static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    inline static bool cursorHidden = false;
public:
    static void RemoveCursor() {
        if (cursorHidden) return;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        if (GetConsoleCursorInfo(hConsole, &info)) {
            CONSOLE_CURSOR_INFO newInfo = info;
            newInfo.dwSize = 100;
            newInfo.bVisible = FALSE;
            SetConsoleCursorInfo(hConsole, &newInfo);
            cursorHidden = true;
        }
    }

    static void ResetCursor() {
        if (!hConsole) hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos = {0, 0};
        SetConsoleCursorPosition(hConsole, pos);
    }

    static void WriteAt(int x, int y, const string& text) {
        if (!hConsole) hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
        SetConsoleCursorPosition(hConsole, pos);
        DWORD written = 0;
        WriteConsoleA(hConsole, text.c_str(), static_cast<DWORD>(text.size()), &written, nullptr);
    }
};

struct Transform {
    enum AngleType { deg, rad };

    double centerX = 0.0;
    double centerY = 0.0;
    double angle   = 0.0;
    AngleType type = deg;

    double cosA = 1.0;
    double sinA = 0.0;

    inline void update() {
        double a = angle;
        if (type == deg) a = angle * M_PI / 180.0;
        cosA = cos(a);
        sinA = sin(a);
    }

    inline void apply(double x, double y, double &rx, double &ry) const {
        double tx = x - centerX;
        double ty = y - centerY;
        rx = tx * cosA - ty * sinA;
        ry = tx * sinA + ty * cosA;
    }
};

class Draw{
    inline static double boundary = 1.5;

    inline static int cols = 0;
    inline static int rows = 0;
    inline static vector<double> xs;
    inline static vector<double> ys;
    inline static int topBorderLen = 0;

public:
    
    static void SetBoundary(double b) {
        boundary = b;

        cols = static_cast<int>(floor((2.0 * boundary) / x_Step)) + 1;
        rows = static_cast<int>(floor((2.0 * boundary) / y_Step)) + 1;
        xs.assign(cols, 0.0);
        ys.assign(rows, 0.0);

        for (int j = 0; j < cols; ++j) {
            xs[j] = -boundary + j * x_Step;
        }

        for (int i = 0; i < rows; ++i) {
            ys[i] = boundary - i * y_Step;
        }
        topBorderLen = cols + 2; 
    }

    static inline char Shade(double val) {
        return (val <= 0.0) ? '*' : ' ';
    }

    template<class ShapeType, typename... Args>
    static void draw(const Transform &T, Args... arg) {
        CursorController::ResetCursor();

        if (cols == 0 || rows == 0) {
            SetBoundary(boundary);
        }

        size_t estimated = static_cast<size_t>((cols + 3) * (rows + 2));
        string output;
        output.reserve(estimated);

        output.append(topBorderLen, '=');
        output.append("\n");

        for (int i = 0; i < rows; ++i) {
            output.push_back('|');
            double y = ys[i];
            for (int j = 0; j < cols; ++j) {
                double x = xs[j];

                pair<double, double> r;
                T.apply(x, y, r.first, r.second);                

                double v = ShapeType::value(r.first, r.second, arg...);
                output.push_back(Shade(v));
            }
            output.append("|\n");
        }

        output.append(topBorderLen, '=');
        output.append("\n");

        CursorController::WriteAt(0, 0, output);
    }
  
    static void drawFunc(function<double(double, double)> func, const Transform &T) {
        CursorController::ResetCursor();

        if (cols == 0 || rows == 0) {
            SetBoundary(boundary);
        }
        
        size_t estimated = static_cast<size_t>((cols + 3) * (rows + 2));
        string output;
        output.reserve(estimated);

        output.append(topBorderLen, '=');
        output.append("\n");

        for (int i = 0; i < rows; ++i) {
            output.push_back('|');
            double y = ys[i];
            for (int j = 0; j < cols; ++j) {
                double x = xs[j];

                pair<double, double> r;
                T.apply(x, y, r.first, r.second);
                
                double v = func(r.first, r.second);
                output.push_back(Shade(v));
            }
            output.append("|\n");
        }

        output.append(topBorderLen, '=');
        output.append("\n");

        CursorController::WriteAt(0, 0, output);
    }  



    static vector<vector<double>> getValueMap(
        const function<double(double, double)>& func,
        const Transform &T
    ) {
        if (cols == 0 || rows == 0) {
            SetBoundary(boundary);
        }

        vector<vector<double>> valueMap;
        valueMap.reserve(rows);

        vector<double> row;
        row.resize(cols);

        for (int i = 0; i < rows; ++i) {
            double y = ys[i];
            for (int j = 0; j < cols; ++j) {
                double x = xs[j];
                pair<double, double> r;
                T.apply(x, y, r.first, r.second);
                row[j] = func(r.first, r.second);
            }
            valueMap.emplace_back(row); 
        }
        return valueMap;
    }

    static vector<vector<double>> MergeValues(
        const vector<vector<double>>& vals1,
        const vector<vector<double>>& vals2,
        const function<double(double, double)>& mergeFunc =
            [](double a, double b) { return min(a, b); }
    ) {

        int rowsLocal = static_cast<int>(vals1.size());
        if (rowsLocal == 0) return {};
        int colsLocal = static_cast<int>(vals1[0].size());

        vector<vector<double>> merged(rowsLocal, vector<double>(colsLocal));

        for (int i = 0; i < rowsLocal; i++) {
            for (int j = 0; j < colsLocal; j++) {
                merged[i][j] = mergeFunc(vals1[i][j], vals2[i][j]);
            }
        }
        return merged;
    }

    static void drawByValue(const vector<vector<double>>& values) {
        CursorController::ResetCursor();

        if (cols == 0 || rows == 0) {
            SetBoundary(boundary);
        }

        if (values.empty()) return;
        int rowsLocal = static_cast<int>(values.size());
        int colsLocal = static_cast<int>(values[0].size());
        
        size_t estimated = static_cast<size_t>((colsLocal + 3) * (rowsLocal + 2));
        string output;
        output.reserve(estimated);

        output.append(colsLocal + 2, '=');
        output.append("\n");

        for (int i = 0; i < rowsLocal; ++i) {
            output.push_back('|');
            const auto &row = values[i];
            for (int j = 0; j < colsLocal; ++j) {
                output.push_back(Shade(row[j]));
            }
            output.append("|\n");
        }

        output.append(colsLocal + 2, '=');
        output.append("\n");

        CursorController::WriteAt(0, 0, output);
    }

};


class FunAnimation {
public:
    static void HeartPopPop(){
    Draw::SetBoundary(1.5);
    CursorController::RemoveCursor();
    double size = 0.7;
    bool up = true;
    Transform T;
    while(true){         
        Draw::drawFunc([&](double x, double y) { 
            return Functions::Heart::value(x, y, 1, size, size); 
        }, T);
        if(up) size += 0.05;
        else size -= 0.05;
        if(size > 1) up = false;
        if(size < 0.7) up = true;
        Sleep(50);
        }
    }
};

class Player {
    double x, y;
    double angle;
public:
    Player() : x(0.0), y(0.0), angle(0.0) {}

    void inline move(double dx, double dy) {
        x += dx;
        y += dy;
    }

    void inline rotate(double dAngle) {
        angle += dAngle;
    }

    pair<double, double> inline getPosition() const {
        return {x, y};
    }

    double inline getAngle() const {
        return angle;
    }

    Transform inline getTransform() const {
        return Transform{
            x,
            y,
            angle,
            Transform::deg
        };
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
    CursorController::RemoveCursor();

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
        Transform playerTransform = player.getTransform();
        playerTransform.update();
        Draw::drawByValue(
            Draw::MergeValues(
                Draw::getValueMap(
                    [](double x, double y) {
                        return Functions::Circle::value(x, y, 0.5);
                    },
                    playerTransform
                ),
                Draw::MergeValues(
                   Draw::getValueMap(
                        [](double x, double y) {
                            return Functions::Square::value(x, y, 0.4);
                        },
                        Transform{1, 1}
                    ),
                    Draw::getValueMap(
                        [](double x, double y) {
                            return Functions::Square::value(x, y ,0.4);
                        },
                        Transform{-1, 0.5}
                    )
                )
            )
        );

        printf("Position: (%.2f, %.2f) Angle: %.2f deg\n", 
            player.getPosition().first,
            player.getPosition().second,
            player.getAngle()
        );
        Sleep(50);
    }  
    return 0;
}
