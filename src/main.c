#include <stdio.h>
#include <activation.h>

int main()
{
    double X[2] = {1.0, 0.5};
    double W1[2][3] = { {0.1, 0.3, 0.5}, {0.2, 0.4, 0.6} };
    double B1[3] = {0.1, 0.2, 0.3};
    double A1[3];
    double Z1[3];
    double W2[3][2] = { {0.1, 0.4}, {0.2, 0.5}, {0.3, 0.6} };
    double B2[2] = {0.1, 0.2};
    double A2[2];
    double Z2[2];
    double W3[2][2] = { {0.1, 0.3}, {0.2, 0.4} };
    double B3[2] = {0.1, 0.2};
    double A3[2];
    double Y[2];
    
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

    for(i = 0; i < 2; i++) {
        a = 0;
        for(j = 0; j < 3; j++) {
            a += W2[j][i] * Z1[j];
        }
        a += B2[i];
        A2[i] = a;
        Z2[i] = sigmoid(A2[i]);
    }

    for(i = 0; i < 2; i++) {
        a = 0;
        for(j = 0; j < 2; j++) {
            a += W3[j][i] * Z2[j];
        }
        a += B3[i];
        A3[i] = a;
        Y[i] = A3[i];
    }

    for(i = 0; i < 3; i++) {
        printf("%f ", A1[i]);
    }
    printf("\n");

    for(i = 0; i < 3; i++) {
        printf("%f ", Z1[i]);
    }
    printf("\n");

    for(i = 0; i < 2; i++) {
        printf("%f ", A2[i]);
    }
    printf("\n");

    for(i = 0; i < 2; i++) {
        printf("%f ", Z2[i]);
    }
    printf("\n");

    for(i = 0; i < 2; i++) {
        printf("%f ", A3[i]);
    }
    printf("\n");

    for(i = 0; i < 2; i++) {
        printf("%f ", Y[i]);
    }
    printf("\n");

    return 0;
}
