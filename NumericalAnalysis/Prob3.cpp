#include "iostream"
#include "math.h"

using namespace std;

double f1(double x){
    return (-0.1 * cos(x) - 0.087);
}

double f2(double x){
    return (-0.1 * cos(x) - 0.087) * cos(x);
}

int main(void){

    double Ans[15][2] = {0};

    for (int K = 1; K <= 15; K++){
        double Cl[2] = {0};
        double I1[2] = {0};
        double I2[2] = {0};

        int n = pow(2, K);
        double a = 0, b = M_PI;

        double h[2] = {0};
        double s[2][2] = {0};

    /*** Trapezoidal ************************************/

        h[0] = (b-a) / n;

        for (int i = 1; i < n; i++){
            double x = a + h[0] * i;
            s[0][0] += 2 * f1(x);
        }
        s[0][0] = 0.5 * (s[0][0] + f1(a) + f1(b)) * h[0];
        I1[0] = -2 / M_PI * s[0][0];

        for (int i = 1; i < n; i++){
            double x = a + h[0] * i;
            s[0][1] += 2 * f2(x);
        }
        s[0][1] = 0.5 * (s[0][1] + f2(a) + f2(b)) * h[0];
        I2[0] = -4 / M_PI * s[0][1];

        Cl[0] = I1[0] + 0.5 * I2[0];

    /******************************************************/

      Ans[K-1][0] = Cl[0];

    /*** Simpson ******************************************/

        h[1] = (b-a) / (2*n);
        double s1[2] = {0};
        double s2[2] = {0};

        for (int i = 1; i <= 2*n-1; i += 2){
            double x = a + h[1] * i;
            s1[0] += 4 * f1(x);
        }
        for (int i = 2; i <= 2*n-2; i += 2){
            double x = a + h[1] * i;
            s2[0] += 2 * f1(x);
        }

        s[1][0] = (s1[0] + s2[0] + f1(a) + f2(b)) * h[1] / 3;
        I1[1] = -2 / M_PI * s[1][0];

        for (int i = 1; i <= 2*n-1; i += 2){
            double x = a + h[1] * i;
            s1[1] += 4 * f2(x);
        }
        for (int i = 2; i <= 2*n-2; i += 2){
            double x = a + h[1] * i;
            s2[1] += 2 * f2(x);
        }

        s[1][1] = (s1[1] + s2[1] + f1(a) + f2(b)) * h[1] / 3;
        I2[1] = -4 / M_PI * s[1][1];

        Cl[1] = I1[1] + 0.5 * I2[1];

    /******************************************************/
    
        Ans[K-1][1] = Cl[1];

    }

    for (int i = 0; i < 15; i++){
        cout << i+1 << " " << Ans[i][0] << " " << Ans[i][1] << endl;
    }

    return 0;
}
