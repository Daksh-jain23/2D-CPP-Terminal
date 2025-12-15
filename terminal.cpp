#include <bits/stdc++.h>
using namespace std;

double Heart(double x, double y, double r = 1.0) {
    return pow(x*x + y*y - 1, 3) - r*x*x*pow(y, 3);
}

double Circle(double x, double y, double r = 1.0) {
    return (x*x)+(y*y)-(r*r);
}

double Ellipse(double x, double y, double a = 1.0, double b = 1){
    return (x*x)/(a*a) + (y*y)/(b*b) - 1;
}

double Hyperbola(double x, double y, double a = 1.0, double b = 1.0){
    return (x*x)/(a*a) - (y*y)/(b*b) - 1;
}

double Astroid(double x, double y, double a = 1.0, double b = 1.0){
    return pow(pow(x/a, 2.0),1/3.0) + pow(pow(y/b, 2.0),1/3.0) - 1;
}

double LuckyLeaf(double x, double y, double r = 1.0){
    return pow(x*x + y*y, 5) - r*r*pow(x*x - y*y, 2);
}

char Shade(double val) {
    if(val <= 0.0) return '*';
    return ' ';                   
}                
 

int main() {
    for(double y = 1.3;y >= -1.3;y-= 0.075){
        for(double x = -1.3;x <= 1.3;x += 0.03){
           cout << Shade(Astroid(x,y));
        }
        cout << endl;
    }
 
    return 0;
}