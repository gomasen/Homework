#include "iostream"
#include "math.h"

using namespace std;

double dxdy(double x, double y){
    return pow(x, 2) - y;
}

int main (void) {
    
    double a, b, eta;
    int n;

    cin >> a >> b >> eta >> n;

    cout << "x," << "y" << endl;

    double h = (b - a) / pow(2, n);

    double x, y;
    x = a;
    y = eta;

    while (x < 2) {
        y = y + h * dxdy(x, y);
        x += h;
    }

    cout << x << "," << y << endl;

    return 0;
}