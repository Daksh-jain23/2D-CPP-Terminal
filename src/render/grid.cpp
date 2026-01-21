#include "render/grid.h"
#include <cmath>

Grid::Grid(double worldWidth, double worldHeight, double x_step, double y_step)
    : width(worldWidth), height(worldHeight), xStep(x_step), yStep(y_step)
{
    cols = static_cast<int>(std::floor(width / xStep)) + 1;
    rows = static_cast<int>(std::floor(height / yStep)) + 1;

    xs.resize(cols);
    ys.resize(rows);

    rebuild();
}

void Grid::rebuild() {
    double xStart = -width * 0.5;
    double yStart =  height * 0.5;

    for (int j = 0; j < cols; j++)
        xs[j] = xStart + j * xStep;

    for (int i = 0; i < rows; i++)
        ys[i] = yStart - i * yStep;
}