#include "iostream"
#include "math.h"

using namespace std;

double dxdy(double x, double y){
    return pow(x, 2) - y;
}

int main (void) {
    
    double a, b, eta;

    a = 0;
    b = 1;
    eta = 2;

    cout << "x," << "y" << endl;

    double h = 0.5;

    double x, y;
    x = a;
    y = eta;

    cout << x << "," << y << endl;

    while (x < 2) {
        y = y + h * dxdy(x, y);
        x += h;
        cout << x << "," << y << endl;
    }

    return 0;
}