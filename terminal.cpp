#include <bits/stdc++.h>
using namespace std;

double Heart(double x, double y, double r = 1.0) {
    return pow(x*x + y*y - 1, 3) - r*x*x*pow(y, 3);
}

char Shade(double val) {
    if(val <= 0.0) return '*';
    return ' ';                   
} 

int main() {
    for(double y = 1.3;y >= -1.3;y-= 0.075){
        for(double x = -1.3;x <= 1.3;x += 0.03){
           cout << Shade(Heart(x,y));
        }
        cout << endl;
    }
 
    return 0;
}