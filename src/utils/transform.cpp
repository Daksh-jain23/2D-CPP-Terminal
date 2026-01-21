#include "utils/transform.h"
#include <cmath>

Transform::Transform() {
    angle = 0.0;
    type = deg;
    cosA = 1.0;
    sinA = 0.0;
}

void Transform::update() {
    double a = angle;
    if (type == deg) {
        if(angle < 0) angle += 360;
        if(angle > 360) angle -= 360;
        a = angle * M_PI / 180.0;
    }
    cosA = cos(a);
    sinA = sin(a);
}

inline void Transform::apply(double xt, double yt, double &rx, double &ry) const{
    double tx = xt - posn.x;
    double ty = yt - posn.y;
    rx = tx * cosA - ty * sinA;
    ry = tx * sinA + ty * cosA;
}
