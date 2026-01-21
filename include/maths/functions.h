#pragma once

// if x,y is inside function - return negative
// else positive
//i.e. returns value of a point in a function

namespace SDF {
    double Line(double x, double y, double m = 1.0, double c = 0.0, double thickness = 0.05);

    double Circle(double x, double y, double r = 1.0);
    
    double Ellipse(double x, double y, double a = 1.0, double b = 1.0);

    double Square(double x, double y, double r = 1.0); 

    double Rectangle(double x, double y, double a = 1.0, double b = 1.0);

    double Heart(double x, double y, double r = 1.0, double a = 1.0, double b = 1.0);

    double Hyperbola(double x, double y, double a = 1.0, double b = 1.0);

    double Astroid(double x, double y, double a = 1.0, double b = 1.0);

    double LuckyLeaf(double x, double y, double r = 1.0);
};