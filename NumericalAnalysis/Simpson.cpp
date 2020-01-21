#include "iostream"
#include "math.h"

using namespace std;

double f(double x){
    return exp(-x);
}

int main(void){
    double a = 0;
    double b = 1;
    int n = pow(2, 20);

    double h = (b-a) / (2*n);
    double s1, s2, s;
    s1 = s2 = s = 0;

    for (int i = 1; i <= 2*n-1; i += 2){
        double x = a + h * i;
        s1 += 4 * f(x);
    }
    for (int i = 2; i <= 2*n-2; i += 2){
        double x = a + h * i;
        s2 += 2 * f(x);
    }

    s = (s1 + s2 + f(a) + f(b)) * h / 3;

    cout << "Ans: " << s << endl;

    return 0;
}