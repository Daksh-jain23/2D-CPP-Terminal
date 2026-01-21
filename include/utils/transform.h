#pragma once
#include "utils/vector2d.h"
#include "utils/angleType.h"

struct Transform {
    Vec2 posn;        
    double angle;
    AngleType type;

    double cosA;
    double sinA;

    Transform();

    /*update saved cosine and sine values, 
    based on angle and type, manage angle bw range */
    void update();            

    // Apply transformation to (xt, yt), output to (rx, ry)
    inline void apply(double xt, double yt, double &rx, double &ry) const;
};