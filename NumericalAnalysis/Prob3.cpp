#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

#define K 1

double f1(double x){
    double a = (-0.1 * cos(x) - 0.087);
    return a;
}

double f2(double x){
    double a = (-0.1 * cos(x) - 0.087) * cos(x);
    return a;
}

double* trapezoidal(double a, double b, int n){
    double h = (b - a) / n;
    double s[2] = {0};
    
    for(int i = 1; i < n; i++){
        double x = a + h * i;
        s[0] += 2 * f1(x);
    }
    
    s[0] = 0.5 * (s[0] + f1(a) + f1(b)) * h;

    for(int i = 1; i < n; i++){
        double x = a + h * i;
        s[1] += 2 * f2(x);
    }
    
    s[1] = 0.5 * (s[1] + f2(a) + f2(b)) * h;

    return s;
}

double* simpson(double a, double b, int n){
    double h = (b - a) / (2 * n);
    double s[2] = {0};
    double s1[2] = {0};
    double s2[2] = {0};
    
    for(int i = 1; i <= 2*n-1; i+=2){
        double x = a + h * i;
        s1[0] += 4 * f1(x);
    }
    for(int i = 2; i <= 2*n-2; i += 2){
        double x = a + h * i;
        s1[1] += 2 * f1(x);
    }
    s[0] = (s1[0] + s1[1] + f1(a) + f1(b)) * h / 3.0;
    
    for(int i = 1; i <= 2*n-1; i+=2){
        double x = a + h * i;
        s2[0] += 4 * f2(x);
    }
    for(int i = 2; i <= 2*n-2; i += 2){
        double x = a + h * i;
        s2[1] += 2 * f2(x);
    }
    s[1] = (s2[0] + s2[1] + f2(a) + f2(b)) * h / 3.0;

    return s;
}

int main(void){
    int n = pow(2, K);
    double a = 0, b = M_PI;
    
    double *s1 = trapezoidal(a,b,n);

    double I1 = -2 / M_PI * *s1;
    double I2 = -4 / M_PI * *(s1+1);
    double tCl = (I1 + 0.5 * I2);
    
    
    double *s2 = simpson(a,b,n);

    I1 = -2 / M_PI * *s2;
    I2 = -4 / M_PI * *(s2+1);
    double sCl = (I1 + 0.5 * I2);
    
    printf("trape = %f : ", tCl);
    printf("simp = %f\n", sCl);

    return 0;
}
