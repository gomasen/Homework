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

    double h = (b - a) / n;
    double s = 0;
    
    for(int i = 1; i < n; i++){
        double x = a + h * i;
        s += 2 * f(x);
    }
    
    s = 0.5 * (s + f(a) + f(b)) * h;

    cout << "Ans: " << s << endl;

    return 0;
}