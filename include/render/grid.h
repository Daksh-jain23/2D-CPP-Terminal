#pragma once
#include <vector>

class Grid {
public:
    int rows = 0, cols = 0;
    double width, height;
    double xStep, yStep;

    std::vector<double> xs, ys;

    Grid(double worldWidth, double worldHeight, double x_step, double y_step);

    void rebuild();
};
