#include <stdio.h>
#include <activation.h>

int main()
{
    double X[2] = {1.0, 0.5};
    double W1[2][3] = { {0.1, 0.3, 0.5}, {0.2, 0.4, 0.6} };
    double B1[3] = {0.1, 0.2, 0.3};
    double A1[3];
    double Z1[3];
    
    int i;
    int j;
    double a;

    for(i = 0; i < 3; i++) {
        a = 0;
        for(j = 0; j < 2; j++) {
            a += W1[j][i] * X[j];
        }
        a += B1[i];
        A1[i] = a;
        Z1[i] = sigmoid(A1[i]);
    }

    for(i = 0; i < 3; i++) {
        printf("%f ", A1[i]);
    }
    printf("\n");

    for(i = 0; i < 3; i++) {
        printf("%f ", Z1[i]);
    }
    printf("\n");

    return 0;
}
