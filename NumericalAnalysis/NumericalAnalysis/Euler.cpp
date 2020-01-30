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

    cout << "n," << "x," << "y" << endl;

    for (int n = 1; n <= 8; n++){
        double h = (b - a) / pow(2, n);

        double x, y;
        x = a;
        y = eta;

        while (x < 2) {
            y = y + h * dxdy(x, y);
            x += h;
        }

        y = y + h * dxdy(x, y);
        cout << n << "," << x << "," << y << endl;
    }
    return 0;
}