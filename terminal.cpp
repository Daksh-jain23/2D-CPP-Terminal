#include <bits/stdc++.h>
using namespace std;
 
int main() {
    for(double y = 1.3;y >= -1.3;y-= 0.075){
        for(double x = -1.3;x <= 1.3;x += 0.03){
           if(pow(x*x + y*y - 1, 3) - x*x*pow(y, 3) < 0) cout << '*';
           else cout << ' ';
        }
        cout << endl;
    }
 
    return 0;
}